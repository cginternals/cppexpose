
#pragma once


#include "duktape-1.4.0/duktape.h"

#include <vector>
#include <string>

#include <cppexpose/scripting/AbstractScriptBackend.h>
#include <cppexpose/function/Function.h>


namespace cppexpose
{


/**
*  @brief
*    Duktape (Ecmascript) scripting backend
*/
class CPPEXPOSE_API DuktapeScriptBackend : public AbstractScriptBackend
{
friend Function & getFunction(duk_context * context, size_t index);


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
    void registerObj(duk_idx_t parentId, PropertyGroup * obj);


protected:
    duk_context           * m_context;   ///< Duktape context
    std::string             m_namespace; ///< Global namespace
    std::vector<Function>   m_functions; ///< List of wrapped functions
};


} // namespace cppexpose
