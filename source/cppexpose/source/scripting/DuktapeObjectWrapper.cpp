
#include "DuktapeObjectWrapper.h"

#include <cppassist/logging/logging.h>

#include <cppexpose/reflection/Object.h>

#include "DuktapeScriptBackend.h"


using namespace cppassist;


namespace
{
    static const char * s_duktapeObjectPointerKey          = "objWrapper";
    static const char * s_duktapePropertyNameKey           = "duk_property_name";
    static const char * s_duktapeFunctionPointerKey        = "duk_function_pointer";
    static const char * s_duktapeStashFreeFunctionIndexKey = "duk_next_function_index";
    static const char * s_duktapeScriptBackend             = "duktapeScriptBackend";
}


namespace cppexpose
{


static DuktapeScriptBackend * getScriptBackend(duk_context * context)
{
    duk_push_global_stash(context);
    duk_get_prop_string(context, -1, s_duktapeScriptBackend);
    void * ptr = duk_get_pointer(context, -1);
    duk_pop_2(context);

    auto backend = static_cast<DuktapeScriptBackend *>(ptr);
    return backend;
}


DuktapeObjectWrapper::DuktapeObjectWrapper(DuktapeScriptBackend * scriptBackend)
: m_obj(nullptr)
, m_scriptBackend(scriptBackend)
, m_context(scriptBackend->m_context)
, m_stashFunctionIndex(0)
{
}

DuktapeObjectWrapper::~DuktapeObjectWrapper()
{
}

void DuktapeObjectWrapper::wrapObject(duk_idx_t parentId, PropertyGroup * obj)
{
    m_obj = obj;

    // Create empty object on the stack
    duk_idx_t objIndex = duk_push_object(m_context);

    duk_push_pointer(m_context, static_cast<void *>(this));
    duk_put_prop_string(m_context, -2, s_duktapeObjectPointerKey);

    // Register object properties
    for (unsigned int i=0; i<obj->numSubValues(); i++) {
        // Get property
        AbstractProperty * prop = obj->property(i);
        std::string propName = prop->name();

        // Register property (ignore sub-objects, they are added later)
        PropertyGroup * group = dynamic_cast<PropertyGroup *>(prop);
        if (!group) {
            // Key (for accessor)
            duk_push_string(m_context, propName.c_str());

            // Getter function object
            duk_push_c_function(m_context, &DuktapeObjectWrapper::getProperty, 0);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, s_duktapePropertyNameKey);

            // Setter function object
            duk_push_c_function(m_context, &DuktapeObjectWrapper::setProperty, 1);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, s_duktapePropertyNameKey);

            // Define property with getter/setter
            duk_def_prop(m_context, objIndex, DUK_DEFPROP_HAVE_GETTER | DUK_DEFPROP_HAVE_SETTER);
        }
    }

    // Register object functions
    Object * scriptable = dynamic_cast<Object *>(obj);
    if (scriptable) {
        const std::vector<Method> & funcs = scriptable->functions();
        for (std::vector<Method>::const_iterator it = funcs.begin(); it != funcs.end(); ++it)
        {
            const Method & func = *it;
            m_scriptBackend->m_functions.push_back(func);

            duk_push_c_function(m_context, wrapFunction, DUK_VARARGS);
            duk_push_int(m_context, m_scriptBackend->m_functions.size() - 1);
            duk_put_prop_string(m_context, -2, s_duktapeFunctionPointerKey);
            duk_put_prop_string(m_context, objIndex, func.name().c_str());
        }
    }

    // Register sub-objects
    for (unsigned int i=0; i<obj->numSubValues(); i++) {
        // Get property
        AbstractProperty * prop = obj->property(i);
        std::string name = prop->name();
        if (PropertyGroup * group = dynamic_cast<PropertyGroup *>(prop)) {
            // Add sub object
            auto objWrapper = new DuktapeObjectWrapper(m_scriptBackend);
            m_wrappedObjects.push_back(objWrapper);

            objWrapper->wrapObject(objIndex, group);
        }
    }

    // Register object in parent object (global if it is no sub-object)
    duk_put_prop_string(m_context, parentId, obj->name().c_str());
}

duk_ret_t DuktapeObjectWrapper::getProperty(duk_context * context)
{
    // Get object
    duk_push_this(context);
    duk_get_prop_string(context, -1, s_duktapeObjectPointerKey);
    void * ptr = duk_get_pointer(context, -1);
    duk_pop_2(context);

    auto objWrapper = static_cast<DuktapeObjectWrapper *>(ptr);
    if (objWrapper)
    {
        DuktapeScriptBackend * scriptBackend = objWrapper->m_scriptBackend;
        PropertyGroup * obj = objWrapper->m_obj;

        // Get property
        duk_push_current_function(context);
        duk_get_prop_string(context, -1, s_duktapePropertyNameKey);
        std::string propName = duk_get_string(context, -1);
        duk_pop_2(context);
        AbstractProperty * property = obj->property(propName);

        if (property)
        {
            Variant value = property->toVariant();

            // Set return value
            scriptBackend->pushToDukStack(context, value);
        }
    }

    return 1;   /*  1 = return value at top
                 *  0 = return 'undefined'
                 * <0 = throw error (use DUK_RET_xxx constants)
                 */
}

duk_ret_t DuktapeObjectWrapper::setProperty(duk_context * context)
{
    auto scriptBackend = getScriptBackend(context);

    // Get value from stack
    Variant value = scriptBackend->fromDukValue(context, -1);
    duk_pop(context);

    // Get object
    duk_push_this(context);
    duk_get_prop_string(context, -1, s_duktapeObjectPointerKey);
    void * ptr = duk_get_pointer(context, -1);
    duk_pop_2(context);

    auto objWrapper = static_cast<DuktapeObjectWrapper *>(ptr);
    if (objWrapper)
    {
        DuktapeScriptBackend * scriptBackend = objWrapper->m_scriptBackend;
        PropertyGroup * obj = objWrapper->m_obj;

        // Get property
        duk_push_current_function(context);
        duk_get_prop_string(context, -1, s_duktapePropertyNameKey);
        std::string propName = duk_get_string(context, -1);
        duk_pop_2(context);
        AbstractProperty * property = obj->property(propName);

        if (property)
        {
            property->fromVariant(value);
        }
    }

    return 0;   /*  1 = return value at top
                 *  0 = return 'undefined'
                 * <0 = throw error (use DUK_RET_xxx constants)
                 */
}

duk_ret_t DuktapeObjectWrapper::wrapFunction(duk_context * context)
{
    auto scriptBackend = getScriptBackend(context);

    duk_idx_t nargs = duk_get_top(context);

    duk_push_current_function(context);
    duk_get_prop_string(context, -1, s_duktapeFunctionPointerKey);
    int funcIndex = duk_get_int(context, -1);

    duk_pop_2(context);

    if (funcIndex >= 0)
    {
        Function & func = scriptBackend->getFunction(context, funcIndex);

        std::vector<Variant> arguments(nargs);
        for (int i = 0; i < nargs; ++i){
            arguments[i] = scriptBackend->fromDukValue(context, 0);
            duk_remove(context, 0);
        }

        Variant value = func.call(arguments);

        if (!value.isNull())
        {
            scriptBackend->pushToDukStack(context, value);
            return 1;
        } else {
            return 0;
        }
    } else {
        warning() << "Error: No valid pointer found." << std::endl;
        return DUK_RET_ERROR;
    }

    /*  1 = return value at top
     *  0 = return 'undefined'
     * <0 = throw error (use DUK_RET_xxx constants)
     */
    return 0;
}


} // namespace cppexpose
