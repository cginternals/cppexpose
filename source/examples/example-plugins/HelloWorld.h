
#pragma once


#include <cppexpose/plugin/Example.h>

#include <cppexpose/plugin/plugin_api.h>


namespace cpplocate {
    class ModuleInfo;
}


/**
*  @brief
*    Hello world example
*/
class HelloWorld : public cppexpose::Example
{
CPPEXPOSE_DECLARE_COMPONENT(HelloWorld, cppexpose::Example)


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] moduleInfo
    *    Module info of the plugin library containing the component (if any)
    */
    HelloWorld(const cpplocate::ModuleInfo & moduleInfo);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~HelloWorld();

    // Virtual cppexpose::Example interface
    virtual void run() override;
};
