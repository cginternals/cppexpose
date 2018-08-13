
#pragma once


#include <vector>

#include "duktape-1.4.0/duktape.h"

#include <cppexpose/ScopedConnection.h>


namespace cppexpose
{
    class Object;
}

namespace cppexpose_script
{


class DuktapeScriptBackend;


/**
*  @brief
*    Scripting representation of a cppexpose::Object
*
*    This class is used to expose a cppexpose::Object to
*    a duktape scripting context.
*/
class DuktapeObjectWrapper
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] scriptBackend
    *    Duktape scripting backend (must not be null)
    *  @param[in] obj
    *    Object to be wrapped (must not be null)
    *
    *  @remarks
    *    Don't call this directly, use DuktapeScriptBackend::getOrCreateObjectWrapper
    *    instead to ensure only one javascript representation exists
    *    for the given cppexpose::Object.
    */
    DuktapeObjectWrapper(DuktapeScriptBackend * scriptBackend, cppexpose::Object * obj);

    /**
    *  @brief
    *    Destructor
    */
    ~DuktapeObjectWrapper();

    /**
    *  @brief
    *    Get wrapped cppexpose::Object (never null)
    */
    cppexpose::Object * object();

    /**
    *  @brief
    *    Get wrapped cppexpose::Object (never null)
    */
    const cppexpose::Object * object() const;

    /**
    *  @brief
    *    Push javascript object representation onto duk stack
    *
    *  @remarks
    *    Either pushes the existing wrapper object (if exists) or
    *    creates a new one on top of the stack.
    *
    *  @see wrapObject()
    */
    void pushToDukStack();


protected:
    /**
    *  @brief
    *    Wrap object into javascript object
    *
    *  @remarks
    *    This function creates a javascript object representing
    *    a cppexpose::Object and puts it on top of the stack. It
    *    also stores the object wrapper into the global stash so
    *    that it can access it later.
    */
    void wrapObject();

    /**
    *  @brief
    *    Callback function for getting a property value
    *
    *  @param[in] context
    *    Duktape context
    *
    *  @return
    *    Duktape status
    *
    *  @remarks
    *    This function is called from the javascript context
    *    to read the value of an object property.
    */
    static duk_ret_t getPropertyValue(duk_context * context);

    /**
    *  @brief
    *    Callback function for setting a property value
    *
    *  @param[in] context
    *    Duktape context
    *
    *  @return
    *    Duktape status
    *
    *  @remarks
    *    This function is called from the javascript context
    *    to write the value of an object property.
    */
    static duk_ret_t setPropertyValue(duk_context * context);

    /**
    *  @brief
    *    Callback function for calling a function
    *
    *  @param[in] context
    *    Duktape context
    *
    *  @return
    *    Duktape status
    *
    *  @remarks
    *    This function is called from the javascript context
    *    to call an object function.
    */
    static duk_ret_t callObjectFunction(duk_context * context);


protected:
    duk_context                       * m_context;       ///< Duktape context
    DuktapeScriptBackend              * m_scriptBackend; ///< Duktape scripting backend
    cppexpose::Object                 * m_obj;           ///< The wrapped object
    int                                 m_stashIndex;    ///< Index of the wrapped object in the stash
    std::vector<DuktapeObjectWrapper *> m_subObjects;    ///< List of wrapped sub-objects

    // Connections to the wrapped object
    cppexpose::ScopedConnection m_beforeDestroyConnection;
    cppexpose::ScopedConnection m_afterAddConnection;
    cppexpose::ScopedConnection m_beforeRemoveConnection;
};


} // namespace cppexpose_script
