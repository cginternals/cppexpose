
#include "DuktapeObjectWrapper.h"

#include <cppassist/logging/logging.h>

#include <cppexpose/reflection/Object.h>

#include "DuktapeScriptBackend.h"


using namespace cppassist;


namespace cppexpose
{


extern const char * s_duktapeFunctionPointerKey;
extern const char * s_duktapeObjectPointerKey;
extern const char * s_duktapePropertyNameKey;


DuktapeObjectWrapper::DuktapeObjectWrapper(DuktapeScriptBackend * scriptBackend, Object * obj)
: m_context(scriptBackend->m_context)
, m_scriptBackend(scriptBackend)
, m_obj(obj)
, m_stashIndex(-1)
{
}

DuktapeObjectWrapper::~DuktapeObjectWrapper()
{
}

void DuktapeObjectWrapper::wrapObject()
{
    // Create empty object on the stack
    duk_idx_t objIndex = duk_push_object(m_context);

    // Save object in stash
    m_stashIndex = m_scriptBackend->getNextStashIndex();
    duk_push_global_stash(m_context);
    duk_push_int(m_context, m_stashIndex);
    duk_dup(m_context, -3);
    duk_put_prop(m_context, -3);
    duk_pop(m_context);

    // Save pointer to wrapped object in javascript object
    duk_push_pointer(m_context, static_cast<void *>(this));
    duk_put_prop_string(m_context, -2, s_duktapeObjectPointerKey);

    // Register object properties
    for (unsigned int i=0; i<m_obj->numSubValues(); i++)
    {
        // Get property
        AbstractProperty * prop = m_obj->property(i);
        std::string propName = prop->name();

        // Register property (ignore sub-objects, they are added later)
        if (!prop->isObject())
        {
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
            duk_def_prop(m_context, objIndex,
                DUK_DEFPROP_HAVE_CONFIGURABLE | DUK_DEFPROP_CONFIGURABLE // configurable (can be deleted)
              | DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE     // enumerable
              | DUK_DEFPROP_HAVE_GETTER | DUK_DEFPROP_HAVE_SETTER        // use getter and setter functions
            );

            // Add empty sub-object placeholder for value properties
            m_subObjects.push_back(nullptr);
        }
    }

    // Register object functions
    const std::vector<Method> & funcs = m_obj->functions();
    for (std::vector<Method>::const_iterator it = funcs.begin(); it != funcs.end(); ++it)
    {
        const Method & method = *it;

        auto & func = static_cast<const Function &>(method);

        duk_push_c_function(m_context, callObjectFunction, DUK_VARARGS);
        duk_push_pointer(m_context, const_cast<Function *>(&func));
        duk_put_prop_string(m_context, -2, s_duktapeFunctionPointerKey);
        duk_put_prop_string(m_context, objIndex, method.name().c_str());
    }

    // Register sub-objects
    for (unsigned int i=0; i<m_obj->numSubValues(); i++)
    {
        // Get property
        AbstractProperty * prop = m_obj->property(i);
        std::string name = prop->name();

        // Check if it is an object
        if (prop->isObject())
        {
            // Wrap sub object
            auto subObj = static_cast<Object *>(prop);
            auto objWrapper = m_scriptBackend->getOrCreateObjectWrapper(subObj);
            objWrapper->pushToDukStack();

            // Register sub-object in parent object
            duk_put_prop_string(m_context, objIndex, subObj->name().c_str());

            // Add wrapper to sub-object
            m_subObjects.push_back(objWrapper);
        }
    }

    // Register callbacks for script engine update
    m_afterAddConnection = m_obj->afterAdd.connect([this](size_t index, cppexpose::AbstractProperty * property)
    {
        // [TODO] Provide an UNUSED() macro in cppassist
        (void)(index);

        // Check if property is an object or a value property
        if (property->isObject())
        {
            assert(m_subObjects.size() == index);

            // Get object
            Object * obj = static_cast<Object *>(property);

            // Get parent object from stash
            duk_push_global_stash(m_context);
            duk_get_prop_index(m_context, -1, m_stashIndex);
            const auto parentIndex = duk_get_top_index(m_context);

            // Wrap object
            const auto objWrapper = m_scriptBackend->getOrCreateObjectWrapper(obj);
            objWrapper->pushToDukStack();

            // Register object in parent object
            duk_put_prop_string(m_context, parentIndex, obj->name().c_str());

            // Clean up
            duk_pop(m_context);
            duk_pop(m_context);

            // Add wrapper to sub-object
            m_subObjects.push_back(objWrapper);
        }
        else
        {
            // Get property
            std::string propName = property->name();

            // Add empty sub-object placeholder for value properties
            m_subObjects.push_back(nullptr);

            // Expose property to scripting
            duk_push_global_stash(m_context);
            duk_get_prop_index(m_context, -1, m_stashIndex);

            duk_push_string(m_context, propName.c_str());

            duk_push_c_function(m_context, &DuktapeObjectWrapper::getPropertyValue, 0);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, s_duktapePropertyNameKey);

            duk_push_c_function(m_context, &DuktapeObjectWrapper::setPropertyValue, 1);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, s_duktapePropertyNameKey);

            duk_def_prop(m_context, -4,
                DUK_DEFPROP_HAVE_CONFIGURABLE | DUK_DEFPROP_CONFIGURABLE // configurable (can be deleted)
              | DUK_DEFPROP_HAVE_ENUMERABLE | DUK_DEFPROP_ENUMERABLE     // enumerable
              | DUK_DEFPROP_HAVE_GETTER | DUK_DEFPROP_HAVE_SETTER        // use getter and setter functions
            );

            duk_pop(m_context);
            duk_pop(m_context);
        }
    });

    m_beforeRemoveConnection = m_obj->beforeRemove.connect([this](size_t index, cppexpose::AbstractProperty * property)
    {
        // Remove property
        duk_push_global_stash(m_context);
        duk_get_prop_index(m_context, -1, m_stashIndex);
        duk_del_prop_string(m_context, -1, property->name().c_str());
        duk_pop(m_context);
        duk_pop(m_context);

        // Delete object wrapper
        auto it = m_subObjects.begin() + index;
        m_subObjects.erase(it);
    });

    m_beforeDestroyConnection = m_obj->beforeDestroy.connect([this](cppexpose::AbstractProperty * property)
    {
        // [TODO] Provide an UNUSED() macro in cppassist
        assert(property == m_obj);
        (void)(property);

        // Get wrapper object
        duk_push_global_stash(m_context);
        duk_get_prop_index(m_context, -1, m_stashIndex);

        // Enumerate properties of wrapper object
        std::vector<std::string> keys;

        duk_enum(m_context, -1, DUK_ENUM_OWN_PROPERTIES_ONLY);
        while (duk_next(m_context, -1, 0))
        {
            std::string key = duk_get_string(m_context, -1);
            keys.push_back(key);

            duk_pop(m_context);
        }

        duk_pop(m_context);

        // Clear wrapper object
        for (auto key : keys)
        {
            duk_del_prop_string(m_context, -1, key.c_str());
        }

        // Release wrapper object
        duk_pop(m_context);
        duk_pop(m_context);
    });
}

void DuktapeObjectWrapper::pushToDukStack()
{
    // If object has not been wrapped before ...
    if (m_stashIndex == -1)
    {
        // Wrap object, leaves wrapper object on top of the stack
        wrapObject();
        return;
    }

    // Push placeholder object
    duk_push_object(m_context);

    // Get object from stash
    duk_push_global_stash(m_context);
    duk_get_prop_index(m_context, -1, m_stashIndex);

    // Replace placeholder
    duk_replace(m_context, -3);

    // Pop global stash
    duk_pop(m_context);
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

    // Check if object wrapper was found
    if (objWrapper)
    {
        // Get object
        Object * obj = objWrapper->m_obj;

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

    // Check if object wrapper was found
    if (objWrapper)
    {
        // Get object
        Object * obj = objWrapper->m_obj;

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
