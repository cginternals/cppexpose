
#include "DuktapeScriptBackend.h"

#include <iostream>
#include <functional>

#include <cppexpose/reflection/Object.h>
#include <cppexpose/reflection/Property.h>
#include <cppexpose/function/Function.h>
#include <cppexpose/variant/Variant.h>
#include <cppexpose/scripting/ScriptContext.h>
#include <cppexpose/typed/DirectValue.h>


namespace
{
    const char * c_duktapeObjectPointerKey = "duk_object_pointer";
    const char * c_duktapeFunctionPointerKey = "duk_function_pointer";
    const char * c_duktapePropertyNameKey = "duk_property_name";
    const char * c_duktapeStashFreeFunctionIndexKey = "duk_next_function_index";
    const char * c_duktapeStashContextPointer = "duk_context_pointer";
}


namespace cppexpose
{


static ScriptContext * getScriptContext(duk_context * context);
static Variant fromDukValue(duk_context * context, duk_idx_t index);
static void pushToDukStack(duk_context * context, const Variant & var);


class DuktapeFunction : public AbstractFunction
{
public:
    DuktapeFunction(duk_context * context, int funcIndex)
    : AbstractFunction("")
    , m_scriptContext(nullptr)
    , m_context(context)
    , m_duktapeStashIndex(funcIndex)
    {
        m_scriptContext = getScriptContext(m_context);
    }

    virtual AbstractFunction * clone()
    {
        return new DuktapeFunction(m_context, m_duktapeStashIndex);
    }

    virtual Variant call(const std::vector<Variant> & args)
    {
        duk_push_global_stash(m_context);
        duk_get_prop_index(m_context, -1, m_duktapeStashIndex);

        for (Variant var : args)
        {
            pushToDukStack(m_context, var);
        }

        duk_int_t error = duk_pcall(m_context, args.size());

        if (error)
        {
            m_scriptContext->scriptException(std::string(duk_safe_to_string(m_context, -1)));
            duk_pop_2(m_context);
            return Variant();
        }

        Variant value = fromDukValue(m_context, -1);
        duk_pop_2(m_context);
        return value;
    }

protected:
    ScriptContext * m_scriptContext;
    duk_context *   m_context;
    int             m_duktapeStashIndex;
};


static ScriptContext * getScriptContext(duk_context * context)
{
    duk_push_global_stash(context);
    duk_get_prop_string(context, -1, c_duktapeStashContextPointer);
    void * context_ptr = duk_get_pointer(context, -1);
    duk_pop_2(context);
    return static_cast<ScriptContext *>(context_ptr);
}

static Variant fromDukValue(duk_context * context, duk_idx_t index = -1)
{
    // Duktape/C function
    if (duk_is_c_function(context, index)) {
        duk_get_prop_string(context, index, c_duktapeFunctionPointerKey);
        AbstractFunction * funcptr = static_cast<AbstractFunction *>(duk_get_pointer(context, -1));
        duk_pop(context);
        return Variant::fromValue<AbstractFunction *>(funcptr);
    }

    // Ecmascript function - will be stored in global stash for access from C++ later.
    if (duk_is_ecmascript_function(context, index)) {
        // Global stash - Only accessible from C/C++ code, not visible from Ecmascript environment.
        duk_push_global_stash(context);

        // Get next free index for function objects in global stash
        if (!duk_get_prop_string(context, -1, c_duktapeStashFreeFunctionIndexKey))
        {
            duk_pop(context); // Pop 'undefined' from the stack that was pushed automatically
            duk_push_int(context, 0);
        }

        int funcIndex = duk_get_int(context, -1);

        // Update index for function objects storage in global stash
        duk_push_int(context, funcIndex+1);
        duk_put_prop_string(context, -3, c_duktapeStashFreeFunctionIndexKey);

        // Copy function object to the top and put it as property into global stash
        duk_dup(context, -3);
        duk_put_prop(context, -3);
        duk_pop(context);

        // [TODO] This produces a memory leak, since the pointer to the function object will never be deleted.
        //        A solution would be to wrap a ref_ptr into the variant, but since there are also function objects
        //        which are not memory-managed (e.g., a C-function that has been passed to the scripting engine),
        //        it would be hard to determine the right use of function-variants.
        //        The script context could of course manage a list of created functions an delete them on destruction,
        //        but that would not solve the problem of "memory leak" while the program is running.
        DuktapeFunction * function = new DuktapeFunction(context, funcIndex);
        return Variant::fromValue<AbstractFunction *>(function);
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
            if (!(duk_is_pointer(context, -1) && fromDukValue(context, -2).value<std::string>() == c_duktapeObjectPointerKey))
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

    std::cerr << "Unknown type found: " << duk_get_type(context, index) << std::endl;
    std::cerr << "Duktape stack dump:" << std::endl;
    duk_dump_context_stderr(context);

    // Unknown
    return Variant();
}

static void pushToDukStack(duk_context * context, const Variant & var)
{
    /*
    virtual bool isEnum() const override = 0;
    virtual bool isArray() const override = 0;
    virtual bool isVariant() const override = 0;
    */

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

static Variant getPropertyValue(AbstractProperty * property)
{
    return property->asTyped()->toVariant();
}

static void setPropertyValue(AbstractProperty * property, const Variant & value)
{
    // Check property
    if (property) {
        // Set value from variant
        property->asTyped()->fromVariant(value);
    }
}

static duk_ret_t getProperty(duk_context * context)
{
    // Get object
    duk_push_this(context);
    duk_get_prop_string(context, -1, c_duktapeObjectPointerKey);
    void * ptr = duk_get_pointer(context, -1);
    duk_pop_2(context);
    Object * obj = static_cast<Object *>(ptr);

    if (obj) {
        // Get property
        duk_push_current_function(context);
        duk_get_prop_string(context, -1, c_duktapePropertyNameKey);
        std::string propName = duk_get_string(context, -1);
        duk_pop_2(context);
        AbstractProperty * property = obj->property(propName);

        if (property) {
            Variant value = getPropertyValue(property);

            // Set return value
            pushToDukStack(context, value);
        }
    }

    return 1;   /*  1 = return value at top
                 *  0 = return 'undefined'
                 * <0 = throw error (use DUK_RET_xxx constants)
                 */
}

static duk_ret_t setProperty(duk_context * context)
{
    // Get value from stack
    Variant value = fromDukValue(context, -1);
    duk_pop(context);

    // Get object
    duk_push_this(context);
    duk_get_prop_string(context, -1, c_duktapeObjectPointerKey);
    void * ptr = duk_get_pointer(context, -1);
    duk_pop_2(context);
    Object * obj = static_cast<Object *>(ptr);

    if (obj) {
        // Get property
        duk_push_current_function(context);
        duk_get_prop_string(context, -1, c_duktapePropertyNameKey);
        std::string propName = duk_get_string(context, -1);
        duk_pop_2(context);
        AbstractProperty * property = obj->property(propName);

        if (property) {
            setPropertyValue(property, value);
        }
    }

    return 0;   /*  1 = return value at top
                 *  0 = return 'undefined'
                 * <0 = throw error (use DUK_RET_xxx constants)
                 */
}

static duk_ret_t wrapFunction(duk_context * context)
{
    duk_idx_t nargs = duk_get_top(context);

    duk_push_current_function(context);
    duk_get_prop_string(context, -1, c_duktapeFunctionPointerKey);
    void * ptr = duk_get_pointer(context, -1);

    duk_pop_2(context);

    if (ptr)
    {
        AbstractFunction * func = static_cast<AbstractFunction *>(ptr);

        std::vector<Variant> arguments(nargs);
        for (int i = 0; i < nargs; ++i){
            arguments[i] = fromDukValue(context, 0);
            duk_remove(context, 0);
        }

        Variant value = func->call(arguments);

        if (!value.isNull())
        {
            pushToDukStack(context, value);
            return 1;
        } else {
            return 0;
        }
    } else {
        std::cerr << "Error: No valid pointer found." << std::endl;
        return DUK_RET_ERROR;
    }

    return 0;   /*  1 = return value at top
                 *  0 = return 'undefined'
                 * <0 = throw error (use DUK_RET_xxx constants)
                 */
}



DuktapeScriptBackend::DuktapeScriptBackend()
: m_context(nullptr)
{
    // Create duktape script context
    m_context = duk_create_heap_default();
}

DuktapeScriptBackend::~DuktapeScriptBackend()
{
    duk_destroy_heap(m_context);
}

void DuktapeScriptBackend::initialize(ScriptContext * scriptContext)
{
    m_scriptContext = scriptContext;

    // Make ScriptContext pointer available through duktape context
    duk_push_global_stash(m_context);
    void * context_ptr = static_cast<void *>(scriptContext);
    duk_push_pointer(m_context, context_ptr);
    duk_put_prop_string(m_context, -2, c_duktapeStashContextPointer);
    duk_pop(m_context);
}

void DuktapeScriptBackend::setGlobalNamespace(const std::string & name)
{
    // Set namespace
    m_namespace = name;

    // Create global object for namespace
    if (m_namespace != "")
    {
        duk_push_global_object(m_context);
        duk_idx_t parentId = duk_get_top_index(m_context);
        duk_push_object(m_context);
        duk_put_prop_string(m_context, parentId, m_namespace.c_str());
        duk_pop(m_context);
    }
}

void DuktapeScriptBackend::registerObject(PropertyGroup * obj)
{
    duk_push_global_object(m_context);

    if (m_namespace != "") {
        duk_push_string(m_context, m_namespace.c_str());
        duk_get_prop(m_context, -2);
    }

    registerObj(duk_get_top_index(m_context), obj);

    if (m_namespace != "") {
        duk_pop(m_context);
    }

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

void DuktapeScriptBackend::registerObj(duk_idx_t parentId, PropertyGroup * obj)
{
    // Create empty object on the stack
    duk_idx_t objIndex = duk_push_object(m_context);

    duk_push_pointer(m_context, static_cast<void *>(obj));
    duk_put_prop_string(m_context, -2, c_duktapeObjectPointerKey);

    // Register object properties
    for (unsigned int i=0; i<obj->numSubValues(); i++) {
        // Get property
        AbstractProperty * prop = obj->property(i);
        std::string propName = prop->name();

        // Check if property is a property group
        PropertyGroup * group = dynamic_cast< PropertyGroup * >(prop);
        if (!group) {
            // Key (for accessor)
            duk_push_string(m_context, propName.c_str());
            // Getter function object
            duk_push_c_function(m_context, getProperty, 0);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, c_duktapePropertyNameKey);
            // Setter function object
            duk_push_c_function(m_context, setProperty, 1);
            duk_push_string(m_context, propName.c_str());
            duk_put_prop_string(m_context, -2, c_duktapePropertyNameKey);

            // Define property with getter/setter
            duk_def_prop(m_context, objIndex, DUK_DEFPROP_HAVE_GETTER | DUK_DEFPROP_HAVE_SETTER);
        }
    }

    // Register object functions
    Object * scriptable = dynamic_cast<Object *>(obj);
    if (scriptable) {
        // [TODO]
        /*
        const std::vector<AbstractFunction *> & funcs = scriptable->functions();
        for (std::vector<AbstractFunction *>::const_iterator it = funcs.begin(); it != funcs.end(); ++it) {
            AbstractFunction * func = *it;

            duk_push_c_function(m_context, wrapFunction, DUK_VARARGS);
            duk_push_pointer(m_context, static_cast<void *>(func));
            duk_put_prop_string(m_context, -2, c_duktapeFunctionPointerKey);
            duk_put_prop_string(m_context, objIndex, func->name().c_str());
        }
        */
    }

    // Register sub-objects
    for (unsigned int i=0; i<obj->numSubValues(); i++) {
        // Get property
        AbstractProperty * prop = obj->property(i);
        std::string name = prop->name();
        if (PropertyGroup * group = dynamic_cast< PropertyGroup * >(prop)) {
            // Add sub object
            registerObj(objIndex, group);
        }
    }

    // Register object in parent object (global if it is no sub-object)
    duk_put_prop_string(m_context, parentId, obj->name().c_str());
}


} // namespace cppexpose
