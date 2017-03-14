
#pragma once


#include <string>

#include <cppexpose/signal/Signal.h>


namespace cppexpose
{


class Object;
class AbstractScriptBackend;
class Variant;


/**
*  @brief
*    The entry point to managing scripting in your application
*/
class CPPEXPOSE_API ScriptContext
{
public:
    /**
    *  @brief
    *    Called when a script triggered an exception
    */
    Signal<const std::string &> scriptException;


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] backend
    *    Name of the backend (supported: "javascript")
    */
    ScriptContext(const std::string & backend = "javascript");

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] backend
    *    Scripting backend (must NOT be null)
    */
    ScriptContext(std::unique_ptr<AbstractScriptBackend> && backend);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ScriptContext();

    /**
    *  @brief
    *    Get global object
    *
    *  @return
    *    Global object (can be null)
    */
    Object * globalObject() const;

    /**
    *  @brief
    *    Set global object
    *
    *  @param[in] obj
    *    Global object (can be null)
    *
    *  @remarks
    *    Sets the root object that is exposed to the scripting environment.
    *    It will be available in the global namespace using the object's name.
    *    The script context does not take ownership over the object.
    *
    *    IMPORTANT: Some scripting backends may require a certain
    *    name for the global object and will issue a warning if
    *    the given object has a different name. The default scripting
    *    backend however ("javascript", base on duktape) supports
    *    any name for the global object.
    */
    void setGlobalObject(Object * obj);

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
    Variant evaluate(const std::string & code);


protected:
    std::unique_ptr<AbstractScriptBackend> m_backend;      ///< Scripting backend (can be null)
    Object                               * m_globalObject; ///< Global object that is exposed to the scripting environment (can be null)
};


} // namespace cppexpose
