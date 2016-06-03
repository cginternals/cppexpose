
#pragma once


#include <vector>
#include <string>

#include <cppexpose/function/Function.h>
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
    Variant fromDukValue(duk_context * context, duk_idx_t index = -1);
    void pushToDukStack(duk_context * context, const Variant & var);
    Function & getFunction(duk_context * context, size_t index);


protected:
    duk_context                         * m_context;        ///< Duktape context
    std::vector<DuktapeObjectWrapper *>   m_wrappedObjects; ///< List of wrapped objects
    std::vector<Function>                 m_functions;      ///< List of wrapped functions
};


} // namespace cppexpose
