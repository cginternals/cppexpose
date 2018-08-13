
#pragma once


#include <string>
#include <map>

#include <cppexpose/Signal.h>

#include <cppexpose-script/cppexpose-script_api.h>


namespace cppexpose
{
    class Object;
    class Variant;
}


namespace cppexpose_script
{


/**
*  @brief
*    Base class for scripting environments
*/
class CPPEXPOSE_SCRIPT_API ScriptEngine
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
    */
    ScriptEngine();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ScriptEngine();

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
    *    Add a global object that is exposed into the scripting environment
    *
    *  @param[in] name
    *    Global object name
    *  @param[in] obj
    *    Global object (must NOT be null)
    */
    virtual void addGlobalObject(const std::string & name, cppexpose::Object * obj);

    /**
    *  @brief
    *    Remove a global object that is exposed into the scripting environment
    *
    *  @param[in] name
    *    Global object name
    */
    virtual void removeGlobalObject(const std::string & name);

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
    virtual cppexpose::Variant evaluate(const std::string & code);


protected:
    virtual void onAddGlobalObject(const std::string & name, cppexpose::Object * obj) = 0;
    virtual void onRemoveGlobalObject(const std::string & name) = 0;
    virtual cppexpose::Variant onEvaluate(const std::string & code) = 0;


protected:
    std::map<std::string, cppexpose::Object *> m_globalObjects; ///< Global objects that are exposed to the scripting environment
};


} // namespace cppexpose_script
