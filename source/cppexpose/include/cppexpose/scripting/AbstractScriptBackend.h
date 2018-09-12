
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class Object;
class ScriptContext;
class Variant;


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
    *    Add a global object that is exposed into the scripting environment
    *
    *  @param[in] obj
    *    Global object (must NOT be null)
    */
    virtual void addGlobalObject(Object * obj) = 0;

    /**
    *  @brief
    *    Remove a global object that is exposed into the scripting environment
    *
    *  @param[in] obj
    *    Global object (must NOT be null)
    */
    virtual void removeGlobalObject(Object * obj) = 0;

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
