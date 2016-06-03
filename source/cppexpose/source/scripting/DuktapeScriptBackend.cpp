
#include "DuktapeScriptBackend.h"

#include <iostream>

#include <cppassist/logging/logging.h>

#include <cppexpose/reflection/Object.h>
#include <cppexpose/variant/Variant.h>
#include <cppexpose/scripting/ScriptContext.h>

#include "DuktapeScriptFunction.h"
#include "DuktapeObjectWrapper.h"


using namespace cppassist;


namespace
{
    static const char * s_duktapeScriptBackendKey          = "duktapeScriptBackend";
    static const char * s_duktapeNextStashFunctionIndexKey = "duktapeNextStashFunctionIndex";
    static const char * s_duktapeFunctionPointerKey        = "duktapeFunctionPointer";
    static const char * s_duktapeObjectPointerKey          = "duk_object_pointer";
    static const char * s_duktapePropertyNameKey           = "duk_property_name";
}


namespace cppexpose
{


DuktapeScriptBackend::DuktapeScriptBackend()
: m_context(nullptr)
{
    // Create duktape script context
    m_context = duk_create_heap_default();
}

DuktapeScriptBackend::~DuktapeScriptBackend()
{
    // Delete wrapped objects
    for (auto * objWrapper : m_objects)
    {
        delete objWrapper;
    }

    // Destroy duktape script context
    duk_destroy_heap(m_context);
}

void DuktapeScriptBackend::initialize(ScriptContext * scriptContext)
{
    // Store script context
    m_scriptContext = scriptContext;

    // Save pointer to script backend in global stash
    duk_push_global_stash(m_context);
    void * context_ptr = static_cast<void *>(this);
    duk_push_pointer(m_context, context_ptr);
    duk_put_prop_string(m_context, -2, s_duktapeScriptBackendKey);
    duk_pop(m_context);
}

void DuktapeScriptBackend::setGlobalNamespace(const std::string &)
{
    // Not supported
}

void DuktapeScriptBackend::registerObject(PropertyGroup * obj)
{
    // Create object wrapper
    auto objWrapper = new DuktapeObjectWrapper(this);
    m_objects.push_back(objWrapper);

    // Wrap object in javascript object and put it into the global object
    duk_push_global_object(m_context);

    objWrapper->wrapObject(duk_get_top_index(m_context), obj);

    duk_pop(m_context);
}

void DuktapeScriptBackend::unregisterObject(PropertyGroup * obj)
{
    // Destroy property in the global object
    duk_push_global_object(m_context);

    duk_del_prop_string(m_context, duk_get_top_index(m_context), obj->name().c_str());

    duk_pop(m_context);
}

Variant DuktapeScriptBackend::evaluate(const std::string & code)
{
    // Check code for errors
    duk_int_t error = duk_peval_string(m_context, code.c_str());

    if (error)
    {
        // Raise exception
        m_scriptContext->scriptException(std::string(duk_safe_to_string(m_context, -1)));

        // Abort and return undefined value
        duk_pop(m_context);
        return Variant();
    }

    // Convert return value to variant
    Variant value = fromDukStack(m_context);
    duk_pop(m_context);
    return value;
}

DuktapeScriptBackend * DuktapeScriptBackend::getScriptBackend(duk_context * context)
{
    // Get stash object
    duk_push_global_stash(context);

    // Get pointer to duktape scripting backend
    duk_get_prop_string(context, -1, s_duktapeScriptBackendKey);
    void * ptr = duk_get_pointer(context, -1);
    duk_pop_2(context);

    // Return duktape scripting backend
    return static_cast<DuktapeScriptBackend *>(ptr);
}

Variant DuktapeScriptBackend::fromDukStack(duk_context * context, duk_idx_t index)
{
    // Wrapped object function
    if (duk_is_c_function(context, index))
    {
        // Get pointer to wrapped function
        duk_get_prop_string(context, index, s_duktapeFunctionPointerKey);
        Function * func = reinterpret_cast<Function *>( duk_get_pointer(context, -1) );
        duk_pop(context);

        // Return wrapped function
        return Variant::fromValue<Function>(*func);
    }

    // Javascript function - will be stored in global stash for access from C++ later
    else if (duk_is_ecmascript_function(context, index))
    {
        // Get stash object
        duk_push_global_stash(context);

        // Get next free index for function objects in global stash
        if (!duk_get_prop_string(context, -1, s_duktapeNextStashFunctionIndexKey))
        {
            // By default, use 0 as index
            duk_pop(context); // Pop 'undefined' from the stack that was pushed automatically
            duk_push_int(context, 0);
        }
        int funcIndex = duk_get_int(context, -1);

        // Increment next free index
        duk_push_int(context, funcIndex + 1);
        duk_put_prop_string(context, -3, s_duktapeNextStashFunctionIndexKey);

        // Copy function object to the top and put it as property into global stash
        duk_dup(context, -3);
        duk_put_prop(context, -3);
        duk_pop(context);

        // Return callable function
        Function function(new DuktapeScriptFunction(this, funcIndex));
        return Variant::fromValue<Function>(function);
    }

    // Number
    else if (duk_is_number(context, index))
    {
        double value = duk_get_number(context, index);
        return Variant(value);
    }

    // Boolean
    else if (duk_is_boolean(context, index))
    {
        bool value = duk_get_boolean(context, index) > 0;
        return Variant(value);
    }

    // String
    else if (duk_is_string(context, index))
    {
        const char *str = duk_get_string(context, index);
        return Variant(str);
    }

    // Array
    else if (duk_is_array(context, index))
    {
        VariantArray array;

        for (unsigned int i = 0; i < duk_get_length(context, index); ++i)
        {
            duk_get_prop_index(context, index, i);
            array.push_back(fromDukStack(context));
            duk_pop(context);
        }

        return array;
    }

    // Object
    else if (duk_is_object(context, index))
    {
        VariantMap map;

        duk_enum(context, index, 0);
        while (duk_next(context, -1, 1))
        {
            // Prevent the pointer to the C++ object that is stored in the Ecmascript object from being serialized
            if (!(duk_is_pointer(context, -1) && fromDukStack(context, -2).value<std::string>() == s_duktapeObjectPointerKey))
            {
                map.insert({ fromDukStack(context, -2).value<std::string>(), fromDukStack(context, -1) });
            }

            duk_pop_2(context);
        }

        duk_pop(context);

        return Variant(map);
    }

    // Pointer
    else if (duk_is_pointer(context, index))
    {
        return Variant::fromValue<void *>(duk_get_pointer(context, index));
    }

    // Undefined
    else if (duk_is_undefined(context, index))
    {
        return Variant();
    }

    // Unknown type
    warning() << "Unknown type found: " << duk_get_type(context, index) << std::endl;
    warning() << "Duktape stack dump:" << std::endl;
    duk_dump_context_stderr(context);
    return Variant();
}

void DuktapeScriptBackend::pushToDukStack(duk_context * context, const Variant & value)
{
    if (value.isBool()) {
        duk_push_boolean(context, value.toBool());
    }

    else if (value.isUnsignedIntegral()) {
        duk_push_number(context, value.toULongLong());
    }

    else if (value.isSignedIntegral() || value.isIntegral()) {
        duk_push_number(context, value.toLongLong());
    }

    else if (value.isFloatingPoint()) {
        duk_push_number(context, value.toDouble());
    }

    else if (value.isString()) {
        duk_push_string(context, value.toString().c_str());
    }

    else if (value.hasType<char*>()) {
        duk_push_string(context, value.value<char*>());
    }

    else if (value.isVariantArray())
    {
        VariantArray variantArray = value.value<VariantArray>();
        duk_idx_t arr_idx = duk_push_array(context);

        for (unsigned int i=0; i<variantArray.size(); i++) {
            pushToDukStack(context, variantArray.at(i));
            duk_put_prop_index(context, arr_idx, i);
        }
    }

    else if (value.isVariantMap())
    {
        VariantMap variantMap = value.value<VariantMap>();
        duk_push_object(context);

        for (const std::pair<std::string, Variant> & pair : variantMap)
        {
            pushToDukStack(context, pair.second);
            duk_put_prop_string(context, -2, pair.first.c_str());
        }
    }
}


} // namespace cppexpose
