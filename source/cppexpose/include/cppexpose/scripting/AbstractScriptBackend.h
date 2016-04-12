
#pragma once


#include <string>

#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


class PropertyGroup;
class ScriptContext;


/**
*  @brief
*    Base class for scripting context backends
*/
class CPPEXPOSE_API AbstractScriptBackend
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractScriptBackend();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractScriptBackend();

    /**
    *  @brief
    *    Get script context that owns the backend
    *
    *  @return
    *    Script context that owns the backend (can be null)
    */
    ScriptContext * scriptContext() const;

    /**
    *  @brief
    *    Initialize scripting backend
    *
    *  @param[in] scriptContext
    *    Script context that owns the backend (must NOT be null)
    *
    *  @remarks
    *    Be sure to assign the script context to m_scriptContext.
    */
    virtual void initialize(ScriptContext * scriptContext) = 0;

    /**
    *  @brief
    *    Set global namespace
    *
    *  @param[in] name
    *    Namespace at which global objects are registered
    *
    *  @see ScriptContext::setGlobalNamespace
    */
    virtual void setGlobalNamespace(const std::string & name) = 0;

    /**
    *  @brief
    *    Expose object to scripting
    *
    *  @param[in] obj
    *    Object to be exposed for scripting (must NOT be null)
    */
    virtual void registerObject(PropertyGroup * obj) = 0;

    /**
    *  @brief
    *    Remove object from scripting
    *
    *  @param[in] obj
    *    Object to be removed from scripting (must NOT be null)
    */
    virtual void unregisterObject(PropertyGroup * obj) = 0;

    /**
    *  @brief
    *    Execute script
    *
    *  @param[in] code
    *    Scripting code
    *
    *  @return
    *    Return value of the executed code
    */
    virtual Variant evaluate(const std::string & code) = 0;


protected:
	ScriptContext * m_scriptContext; ///< Script context holding this backend
};


} // namespace cppexpose
