
#include "DuktapeScriptBackend.h"

#include <cppassist/logging/logging.h>

#include <cppexpose/reflection/Object.h>
#include <cppexpose/scripting/ScriptContext.h>

#include "DuktapeScriptFunction.h"
#include "DuktapeObjectWrapper.h"


using namespace cppassist;


namespace cppexpose
{


const char * s_duktapeScriptBackendKey   = "duktapeScriptBackend";
const char * s_duktapeNextStashIndexKey  = "duktapeNextStashFunctionIndex";
const char * s_duktapeFunctionPointerKey = "duktapeFunctionPointer";
const char * s_duktapeObjectPointerKey   = "duktapeObjectPointer";
const char * s_duktapePropertyNameKey    = "duktapePropertyName";


DuktapeScriptBackend::DuktapeScriptBackend()
: m_context(nullptr)
{
    // Create duktape script context
    m_context = duk_create_heap_default();
}

DuktapeScriptBackend::~DuktapeScriptBackend()
{
    // Disconnect from Object::beforeDestroy signals
    for (auto & objectWrapper : m_objectWrappers)
    {
        objectWrapper.second.second.disconnect();
    }

    // Destroy duktape script context
    duk_destroy_heap(m_context);
}

void DuktapeScriptBackend::initialize(ScriptContext * scriptContext)
{
    // Store script context
    m_scriptContext = scriptContext;

    // Get stash
    duk_push_global_stash(m_context);

    // Save pointer to script backend in global stash
    void * context_ptr = static_cast<void *>(this);
    duk_push_pointer(m_context, context_ptr);
    duk_put_prop_string(m_context, -2, s_duktapeScriptBackendKey);

    // Initialize next index for storing functions and objects in the stash
    duk_push_int(m_context, 0);
    duk_put_prop_string(m_context, -2, s_duktapeNextStashIndexKey);

    // Release stash
    duk_pop(m_context);
}

void DuktapeScriptBackend::addGlobalObject(Object * obj)
{
    // Wrap object in javascript object
    const auto objWrapper = getOrCreateObjectWrapper(obj);

    // Get global object
    duk_push_global_object(m_context);
    const auto parentIndex = duk_get_top_index(m_context);

    // Push wrapper object
    objWrapper->pushToDukStack();

    // Register object in the global object
    duk_put_prop_string(m_context, parentIndex, obj->name().c_str());

    // Pop global object from stack
    duk_pop(m_context);
}

void DuktapeScriptBackend::removeGlobalObject(Object * obj)
{
    // Remove property in the global object
    duk_push_global_object(m_context);
    duk_del_prop_string(m_context, duk_get_top_index(m_context), obj->name().c_str());
    duk_pop(m_context);
}

Variant DuktapeScriptBackend::evaluate(const std::string & code)
{
    // Execute code
    duk_int_t error = duk_peval_string(m_context, code.c_str());

    // Check for errors
    if (error)
    {
        // Raise exception
        m_scriptContext->scriptException(std::string(duk_safe_to_string(m_context, -1)));

        // Abort and return undefined value
        duk_pop(m_context);
        return Variant();
    }

    // Convert return value to variant
    Variant value = fromDukStack();
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

Variant DuktapeScriptBackend::fromDukStack(duk_idx_t index)
{
    // Wrapped object function
    if (duk_is_c_function(m_context, index))
    {
        // Get pointer to wrapped function
        duk_get_prop_string(m_context, index, s_duktapeFunctionPointerKey);
        Function * func = reinterpret_cast<Function *>( duk_get_pointer(m_context, -1) );
        duk_pop(m_context);

        // Return wrapped function
        return Variant::fromValue<Function>(*func);
    }

    // Javascript function - will be stored in global stash for access from C++ later
    else if (duk_is_ecmascript_function(m_context, index))
    {
        // Get stash object
        duk_push_global_stash(m_context);

        // Get next free index in global stash
        int funcIndex = getNextStashIndex();
        duk_push_int(m_context, funcIndex);

        // Copy function object to the top and put it as property into global stash
        duk_dup(m_context, -3);
        duk_put_prop(m_context, -3);

        // Close stash
        duk_pop(m_context);

        // Return callable function
        Function function(cppassist::make_unique<DuktapeScriptFunction>(this, funcIndex));
        return Variant::fromValue<Function>(function);
    }

    // Number
    else if (duk_is_number(m_context, index))
    {
        double value = duk_get_number(m_context, index);
        return Variant(value);
    }

    // Boolean
    else if (duk_is_boolean(m_context, index))
    {
        bool value = duk_get_boolean(m_context, index) > 0;
        return Variant(value);
    }

    // String
    else if (duk_is_string(m_context, index))
    {
        const char *str = duk_get_string(m_context, index);
        return Variant(str);
    }

    // Array
    else if (duk_is_array(m_context, index))
    {
        VariantArray array;

        for (unsigned int i = 0; i < duk_get_length(m_context, index); ++i)
        {
            duk_get_prop_index(m_context, index, i);
            array.push_back(fromDukStack());
            duk_pop(m_context);
        }

        return array;
    }

    // Object
    else if (duk_is_object(m_context, index))
    {
        VariantMap map;

        duk_enum(m_context, index, 0);
        while (duk_next(m_context, -1, 1))
        {
            // Prevent the pointer to the C++ object that is stored in the Ecmascript object from being serialized
            if (!(duk_is_pointer(m_context, -1) && fromDukStack(-2).value<std::string>() == s_duktapeObjectPointerKey))
            {
                map.insert({ fromDukStack(-2).value<std::string>(), fromDukStack(-1) });
            }

            duk_pop_2(m_context);
        }

        duk_pop(m_context);

        return Variant(map);
    }

    // Pointer
    else if (duk_is_pointer(m_context, index))
    {
        return Variant::fromValue<void *>(duk_get_pointer(m_context, index));
    }

    // Undefined
    else if (duk_is_undefined(m_context, index))
    {
        return Variant();
    }

    // Unknown type
    warning() << "Unknown type found: " << duk_get_type(m_context, index) << std::endl;
    warning() << "Duktape stack dump:" << std::endl;
    duk_dump_context_stderr(m_context);
    return Variant();
}

void DuktapeScriptBackend::pushToDukStack(const Variant & value)
{
    if (value.isBool()) {
        duk_push_boolean(m_context, value.toBool());
    }

    else if (value.isUnsignedIntegral()) {
        duk_push_number(m_context, value.toULongLong());
    }

    else if (value.isSignedIntegral() || value.isIntegral()) {
        duk_push_number(m_context, value.toLongLong());
    }

    else if (value.isFloatingPoint()) {
        duk_push_number(m_context, value.toDouble());
    }

    else if (value.isString()) {
        duk_push_string(m_context, value.toString().c_str());
    }

    else if (value.hasType<char*>()) {
        duk_push_string(m_context, value.value<char*>());
    }

    else if (value.isVariantArray())
    {
        VariantArray variantArray = value.value<VariantArray>();
        duk_idx_t arr_idx = duk_push_array(m_context);

        for (unsigned int i=0; i<variantArray.size(); i++) {
            pushToDukStack(variantArray.at(i));
            duk_put_prop_index(m_context, arr_idx, i);
        }
    }

    else if (value.isVariantMap())
    {
        VariantMap variantMap = value.value<VariantMap>();
        duk_push_object(m_context);

        for (const std::pair<std::string, Variant> & pair : variantMap)
        {
            pushToDukStack(pair.second);
            duk_put_prop_string(m_context, -2, pair.first.c_str());
        }
    }

    else if (value.hasType<cppexpose::Object *>())
    {
        const auto object = value.value<cppexpose::Object *>();
        const auto objWrapper = getOrCreateObjectWrapper(object);
        objWrapper->pushToDukStack();
    }

    else
    {
        warning() << "Unknown variant type found: " << value.type().name();
        duk_push_undefined(m_context);
    }
}

DuktapeObjectWrapper * DuktapeScriptBackend::getOrCreateObjectWrapper(cppexpose::Object * object)
{
    // Check if wrapper exists
    const auto itr = m_objectWrappers.find(object);
    if (itr != m_objectWrappers.end())
    {
        return itr->second.first.get();
    }

    // Wrap object
    auto wrapper = cppassist::make_unique<DuktapeObjectWrapper>(this, object);

    // Delete wrapper when object is destroyed
    // The connection will be deleted when this backend is destroyed
    const auto beforeDestroy = object->beforeDestroy.connect([this, object](AbstractProperty *)
    {
        m_objectWrappers.erase(object);
    });

    // Save wrapper for later
    m_objectWrappers[object] = {std::move(wrapper), beforeDestroy};

    // Return object wrapper
    return m_objectWrappers[object].first.get();
}

int DuktapeScriptBackend::getNextStashIndex()
{
    // Get stash object
    duk_push_global_stash(m_context);

    // Get next free index for functions or objects in global stash
    duk_get_prop_string(m_context, -1, s_duktapeNextStashIndexKey);
    int index = duk_get_int(m_context, -1);

    // Increment next free index
    duk_push_int(m_context, index + 1);
    duk_put_prop_string(m_context, -3, s_duktapeNextStashIndexKey);

    // Clean up stack
    duk_pop(m_context);
    duk_pop(m_context);

    // Return index
    return index;
}


} // namespace cppexpose
