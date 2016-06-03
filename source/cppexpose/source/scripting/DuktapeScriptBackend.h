
#pragma once


#include <vector>
#include <string>

#include <cppexpose/scripting/AbstractScriptBackend.h>

#include "duktape-1.4.0/duktape.h"


namespace cppexpose
{


class PropertyGroup;
class DuktapeObjectWrapper;


/**
*  @brief
*    Duktape (javascript) scripting backend
*/
class CPPEXPOSE_API DuktapeScriptBackend : public AbstractScriptBackend
{
    friend class DuktapeScriptFunction;
    friend class DuktapeObjectWrapper;


public:
    /**
    *  @brief
    *    Constructor
    */
    DuktapeScriptBackend();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DuktapeScriptBackend();

    // Virtual AbstractScriptBackend interface
    virtual void initialize(ScriptContext * scriptContext) override;
    virtual void setGlobalNamespace(const std::string & name) override;
    virtual void registerObject(PropertyGroup * obj) override;
    virtual void unregisterObject(PropertyGroup * obj) override;
    virtual Variant evaluate(const std::string & code) override;


protected:
    /**
    *  @brief
    *    Get duktape scripting backend from duktape context
    *
    *  @param[in] context
    *    Duktape context
    *
    *  @return
    *    Duktape scripting backend (can be null)
    */
    static DuktapeScriptBackend * getScriptBackend(duk_context * context);

    /**
    *  @brief
    *    Get value from the duktape stack and convert it into a variant
    *
    *  @param[in] context
    *    Duktape context
    *  @param[in] index
    *    Stack index
    *
    *  @return
    *    Variant value
    */
    Variant fromDukStack(duk_context * context, duk_idx_t index = -1);

    /**
    *  @brief
    *    Push value to the duktape stack
    *
    *  @param[in] context
    *    Duktape context
    *  @param[in] value
    *    Variant value
    */
    void pushToDukStack(duk_context * context, const Variant & value);


protected:
    duk_context                         * m_context;   ///< Duktape context
    std::vector<DuktapeObjectWrapper *>   m_objects;   ///< List of wrapped objects
};


} // namespace cppexpose
