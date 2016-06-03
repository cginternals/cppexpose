
#pragma once


#include <vector>

#include "duktape-1.4.0/duktape.h"

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class PropertyGroup;
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
    *    Duktape scripting backend
    */
    DuktapeObjectWrapper(DuktapeScriptBackend * scriptBackend);

    /**
    *  @brief
    *    Destructor
    */
    ~DuktapeObjectWrapper();

    void wrapObject(duk_idx_t parentId, PropertyGroup * obj);


protected:
    static duk_ret_t getProperty(duk_context * context);
    static duk_ret_t setProperty(duk_context * context);
    static duk_ret_t wrapFunction(duk_context * context);


protected:
    PropertyGroup                       * m_obj;
    DuktapeScriptBackend                * m_scriptBackend;
    duk_context                         * m_context;
    int                                   m_stashFunctionIndex;
    std::vector<DuktapeObjectWrapper *>   m_wrappedObjects;     ///< List of wrapped sub-objects
};


} // namespace cppexpose
