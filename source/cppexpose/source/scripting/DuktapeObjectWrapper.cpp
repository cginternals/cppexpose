
#include "DuktapeObjectWrapper.h"

#include <cppassist/logging/logging.h>

#include <cppexpose/reflection/Object.h>

#include "DuktapeScriptBackend.h"


using namespace cppassist;


namespace
{
    static const char * s_duktapeScriptBackendKey   = "duktapeScriptBackend";
    static const char * s_duktapeNextStashIndexKey  = "duktapeNextStashFunctionIndex";
    static const char * s_duktapeFunctionPointerKey = "duktapeFunctionPointer";
    static const char * s_duktapeObjectPointerKey   = "duktapeObjectPointer";
    static const char * s_duktapePropertyNameKey    = "duktapePropertyName";
}


namespace cppexpose
{


DuktapeObjectWrapper::DuktapeObjectWrapper(DuktapeScriptBackend * scriptBackend)
: m_context(scriptBackend->m_context)
, m_scriptBackend(scriptBackend)
, m_obj(nullptr)
, m_stashIndex(-1)
{
}

DuktapeObjectWrapper::~DuktapeObjectWrapper()
{
    // Delete wrapped sub-objects
    for (auto * objWrapper : m_subObjects)
    {
        delete objWrapper;
    }
}

void DuktapeObjectWrapper::wrapObject(duk_idx_t parentIndex, PropertyGroup * obj)
{
    // Store pointer to wrapped object
    m_obj = obj;

    // Create empty object on the stack
    duk_idx_t objIndex = duk_push_object(m_context);

    // Save object in stash
    duk_push_global_stash(m_context);
    duk_push_int(m_context, m_scriptBackend->getNextStashIndex());
    duk_dup(m_context, -3);
    duk_put_prop(m_context, -3);
    duk_pop(m_context);

    // Save pointer to wrapped object in javascript object
    duk_push_pointer(m_context, static_cast<void *>(this));
    duk_put_prop_string(m_context, -2, s_duktapeObjectPointerKey);

    // Register object properties
    for (unsigned int i=0; i<obj->numSubValues(); i++)
    {
        // Get property
        AbstractProperty * prop = obj->property(i);
        std::string propName = prop->name();

        // Register property (ignore sub-objects, they are added later)
        PropertyGroup * group = dynamic_cast<PropertyGroup *>(prop);
        if (!group) {
            // Key (for accessor)
            duk_push_string(m_context, propName.c_str());

            // Getter function object
            duk_push_c_function(m_context, &DuktapeObjectWrapper::getPropertyValue, 0);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, s_duktapePropertyNameKey);

            // Setter function object
            duk_push_c_function(m_context, &DuktapeObjectWrapper::setPropertyValue, 1);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, s_duktapePropertyNameKey);

            // Define property with getter/setter
            duk_def_prop(m_context, objIndex, DUK_DEFPROP_HAVE_GETTER | DUK_DEFPROP_HAVE_SETTER);
        }
    }

    // Check if object may have functions
    Object * scriptable = dynamic_cast<Object *>(obj);
    if (scriptable) {
        // Register object functions
        const std::vector<Method> & funcs = scriptable->functions();
        for (std::vector<Method>::const_iterator it = funcs.begin(); it != funcs.end(); ++it)
        {
            const Method & method = *it;

            auto & func = static_cast<const Function &>(method);

            duk_push_c_function(m_context, callObjectFunction, DUK_VARARGS);
            duk_push_pointer(m_context, const_cast<Function *>(&func));
            duk_put_prop_string(m_context, -2, s_duktapeFunctionPointerKey);
            duk_put_prop_string(m_context, objIndex, method.name().c_str());
        }
    }

    // Register sub-objects
    for (unsigned int i=0; i<obj->numSubValues(); i++) {
        // Get property
        AbstractProperty * prop = obj->property(i);
        std::string name = prop->name();
        if (PropertyGroup * group = dynamic_cast<PropertyGroup *>(prop)) {
            // Create object wrapper
            auto objWrapper = new DuktapeObjectWrapper(m_scriptBackend);
            m_subObjects.push_back(objWrapper);

            // Add sub object
            objWrapper->wrapObject(objIndex, group);
        }
    }

    // Register object in parent object (global if it is no sub-object)
    duk_put_prop_string(m_context, parentIndex, obj->name().c_str());
}

duk_ret_t DuktapeObjectWrapper::getPropertyValue(duk_context * context)
{
    // Get script backend
    auto scriptBackend = DuktapeScriptBackend::getScriptBackend(context);

    // Get object wrapper
    duk_push_this(context);
    duk_get_prop_string(context, -1, s_duktapeObjectPointerKey);
    auto objWrapper = static_cast<DuktapeObjectWrapper *>( duk_get_pointer(context, -1) );
    duk_pop_2(context);

    if (objWrapper)
    {
        // Get object
        PropertyGroup * obj = objWrapper->m_obj;

        // Get property name
        duk_push_current_function(context);
        duk_get_prop_string(context, -1, s_duktapePropertyNameKey);
        std::string propName = duk_get_string(context, -1);
        duk_pop_2(context);

        // Get property
        AbstractProperty * property = obj->property(propName);
        if (property)
        {
            // Return property value
            Variant value = property->toVariant();
            scriptBackend->pushToDukStack(value);
        }
    }

    // Return status
    //     1: return value at top
    //     0: return 'undefined'
    //   < 0: return error (use DUK_RET_xxx constants)
    return 1;
}

duk_ret_t DuktapeObjectWrapper::setPropertyValue(duk_context * context)
{
    // Get script backend
    auto scriptBackend = DuktapeScriptBackend::getScriptBackend(context);

    // Get value from stack
    Variant value = scriptBackend->fromDukStack(-1);
    duk_pop(context);

    // Get object wrapper
    duk_push_this(context);
    duk_get_prop_string(context, -1, s_duktapeObjectPointerKey);
    auto objWrapper = static_cast<DuktapeObjectWrapper *>( duk_get_pointer(context, -1) );
    duk_pop_2(context);

    if (objWrapper)
    {
        // Get object
        PropertyGroup * obj = objWrapper->m_obj;

        // Get property name
        duk_push_current_function(context);
        duk_get_prop_string(context, -1, s_duktapePropertyNameKey);
        std::string propName = duk_get_string(context, -1);
        duk_pop_2(context);

        // Get property
        AbstractProperty * property = obj->property(propName);
        if (property)
        {
            // Set property value
            property->fromVariant(value);
        }
    }

    // Return status
    //     1: return value at top
    //     0: return 'undefined'
    //   < 0: return error (use DUK_RET_xxx constants)
    return 0;
}

duk_ret_t DuktapeObjectWrapper::callObjectFunction(duk_context * context)
{
    // Get script backend
    auto scriptBackend = DuktapeScriptBackend::getScriptBackend(context);

    // Determine number of arguments
    duk_idx_t nargs = duk_get_top(context);

    // Get function pointer
    duk_push_current_function(context);
    duk_get_prop_string(context, -1, s_duktapeFunctionPointerKey);
    Function * func = reinterpret_cast<Function *>( duk_get_pointer(context, -1) );
    duk_pop_2(context);

    // Is function valid?
    if (func)
    {
        // Get all arguments from the stack and convert them into variants
        std::vector<Variant> arguments(nargs);
        for (int i = 0; i < nargs; ++i){
            arguments[i] = scriptBackend->fromDukStack(0);
            duk_remove(context, 0);
        }

        // Call function
        Variant value = func->call(arguments);

        // Check return value
        if (!value.isNull())
        {
            // Push return value to stack
            scriptBackend->pushToDukStack(value);
            return 1;
        }
        else
        {
            // No return value
            return 0;
        }
    }

    // No valid function found
    warning() << "Error: No valid function pointer found." << std::endl;
    return DUK_RET_ERROR;
}


} // namespace cppexpose
