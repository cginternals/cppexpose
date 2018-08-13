
#pragma once


#include <string>
#include <map>

#include <cppexpose/signal/Signal.h>

#include <cppexpose-script/cppexpose-script_api.h>


namespace cppexpose
{
    class Object;
    class Variant;
}

namespace cppexpose_script
{


class AbstractScriptBackend;


/**
*  @brief
*    The entry point to managing scripting in your application
*/
class CPPEXPOSE_SCRIPT_API ScriptContext
{
public:
    /**
    *  @brief
    *    Called when a script triggered an exception
    */
    cppexpose::Signal<const std::string &> scriptException;


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
    *    Get global objects
    *
    *  @return
    *    List of global objects
    */
    const std::map<std::string, cppexpose::Object *> & globalObjects() const;

    /**
    *  @brief
    *    Add global object
    *
    *  @param[in] name
    *    Global object name
    *  @param[in] obj
    *    Global object (must NOT be null)
    *
    *  @remarks
    *    Adds a global object that is exposed to the scripting environment.
    *    It will be available in the global namespace using the object's name.
    *    The script context does not take ownership over the object.
    */
    void addGlobalObject(const std::string & name, cppexpose::Object * obj);

    /**
    *  @brief
    *    Remove global object
    *
    *  @param[in] name
    *    Global object name
    *
    *  @remarks
    *    Removes a global object that is exposed to the scripting environment.
    */
    void removeGlobalObject(const std::string & name);

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
    cppexpose::Variant evaluate(const std::string & code);


protected:
    std::unique_ptr<AbstractScriptBackend>     m_backend;       ///< Scripting backend (can be null)
    std::map<std::string, cppexpose::Object *> m_globalObjects; ///< Global objects that are exposed to the scripting environment
};


} // namespace cppexpose_script
