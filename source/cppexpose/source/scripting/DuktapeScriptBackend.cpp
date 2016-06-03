
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
    static const char * s_duktapeObjectPointerKey          = "duk_object_pointer";
    static const char * s_duktapePropertyNameKey           = "duk_property_name";
    static const char * s_duktapeFunctionPointerKey        = "duk_function_pointer";
    static const char * s_duktapeStashFreeFunctionIndexKey = "duk_next_function_index";
    static const char * s_duktapeScriptBackend             = "duktapeScriptBackend";
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
    duk_put_prop_string(m_context, -2, s_duktapeScriptBackend);
    duk_pop(m_context);
}

void DuktapeScriptBackend::setGlobalNamespace(const std::string &)
{
    // Not supported
}

void DuktapeScriptBackend::registerObject(PropertyGroup * obj)
{
    auto objWrapper = new DuktapeObjectWrapper(this);
    m_wrappedObjects.push_back(objWrapper);

    duk_push_global_object(m_context);
    objWrapper->wrapObject(duk_get_top_index(m_context), obj);
    duk_pop(m_context);
}

void DuktapeScriptBackend::unregisterObject(PropertyGroup * obj)
{
    duk_push_global_object(m_context);
    duk_del_prop_string(m_context, duk_get_top_index(m_context), obj->name().c_str());
    duk_pop(m_context);
}

Variant DuktapeScriptBackend::evaluate(const std::string & code)
{
    duk_int_t error = duk_peval_string(m_context, code.c_str());

    if (error)
    {
        m_scriptContext->scriptException(std::string(duk_safe_to_string(m_context, -1)));
        duk_pop(m_context);
        return Variant();
    }

    Variant value = fromDukValue(m_context);
    duk_pop(m_context);

    return value;
}

Variant DuktapeScriptBackend::fromDukValue(duk_context * context, duk_idx_t index)
{
    // Duktape/C function
    if (duk_is_c_function(context, index)) {
        duk_get_prop_string(context, index, s_duktapeFunctionPointerKey);
        int funcIndex = duk_get_int(context, -1);
        Function & func = getFunction(context, funcIndex);
        duk_pop(context);
        return Variant::fromValue<Function>(func);
    }

    // Ecmascript function - will be stored in global stash for access from C++ later.
    if (duk_is_ecmascript_function(context, index)) {
        // Global stash - Only accessible from C/C++ code, not visible from Ecmascript environment.
        duk_push_global_stash(context);

        // Get next free index for function objects in global stash
        if (!duk_get_prop_string(context, -1, s_duktapeStashFreeFunctionIndexKey))
        {
            duk_pop(context); // Pop 'undefined' from the stack that was pushed automatically
            duk_push_int(context, 0);
        }

        int funcIndex = duk_get_int(context, -1);

        // Update index for function objects storage in global stash
        duk_push_int(context, funcIndex+1);
        duk_put_prop_string(context, -3, s_duktapeStashFreeFunctionIndexKey);

        // Copy function object to the top and put it as property into global stash
        duk_dup(context, -3);
        duk_put_prop(context, -3);
        duk_pop(context);

        // Return callable function
        Function function(new DuktapeScriptFunction(this, funcIndex));
        return Variant::fromValue<Function>(function);
    }

    // Number
    else if (duk_is_number(context, index)) {
        double value = duk_get_number(context, index);
        return Variant(value);
    }

    // Bool
    else if (duk_is_boolean(context, index)) {
        bool value = duk_get_boolean(context, index) > 0;
        return Variant(value);
    }

    // String
    else if (duk_is_string(context, index)) {
        const char *str = duk_get_string(context, index);
        return Variant(str);
    }

    // Array
    else if (duk_is_array(context, index)) {
        VariantArray array;
        for (unsigned int i = 0; i < duk_get_length(context, index); ++i)
        {
            duk_get_prop_index(context, index, i);
            array.push_back(fromDukValue(context));
            duk_pop(context);
        }
        return array;
    }

    // Object
    else if (duk_is_object(context, index)) {
        VariantMap map;

        duk_enum(context, index, 0);
        while (duk_next(context, -1, 1)) {
            // Prevent the pointer to the C++ object that is stored in the Ecmascript Object from being serialized.
            if (!(duk_is_pointer(context, -1) && fromDukValue(context, -2).value<std::string>() == s_duktapeObjectPointerKey))
            {
                map.insert({ fromDukValue(context, -2).value<std::string>(), fromDukValue(context, -1) });
            }
            duk_pop_2(context);
        }
        duk_pop(context);

        return Variant(map);
    }

    // Pointer
    else if (duk_is_pointer(context, index)) {
        return Variant::fromValue<void *>(duk_get_pointer(context, index));
    }

    // Undefined
    else if (duk_is_undefined(context, index)) {
        return Variant();
    }

    warning() << "Unknown type found: " << duk_get_type(context, index) << std::endl;
    warning() << "Duktape stack dump:" << std::endl;
    duk_dump_context_stderr(context);

    // Unknown
    return Variant();
}

void DuktapeScriptBackend::pushToDukStack(duk_context * context, const Variant & var)
{
    if (var.isBool()) {
        duk_push_boolean(context, var.toBool());
    }

    else if (var.isUnsignedIntegral()) {
        duk_push_number(context, var.toULongLong());
    }

    else if (var.isSignedIntegral() || var.isIntegral()) {
        duk_push_number(context, var.toLongLong());
    }

    else if (var.isFloatingPoint()) {
        duk_push_number(context, var.toDouble());
    }

    else if (var.isString()) {
        duk_push_string(context, var.toString().c_str());
    }

    else if (var.hasType<char*>()) {
        duk_push_string(context, var.value<char*>());
    }

    else if (var.isVariantArray()) {
        VariantArray variantArray = var.value<VariantArray>();
        duk_idx_t arr_idx = duk_push_array(context);
        for (unsigned int i=0; i<variantArray.size(); i++) {
            pushToDukStack(context, variantArray.at(i));
            duk_put_prop_index(context, arr_idx, i);
        }
    }

    else if (var.isVariantMap()) {
        VariantMap variantMap = var.value<VariantMap>();
        duk_push_object(context);

        for (const std::pair<std::string, Variant> & pair : variantMap)
        {
            pushToDukStack(context, pair.second);
            duk_put_prop_string(context, -2, pair.first.c_str());
        }
    }
}

Function & DuktapeScriptBackend::getFunction(duk_context * context, size_t index)
{
    return m_functions[index];
}


} // namespace cppexpose
