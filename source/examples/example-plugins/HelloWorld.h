
#pragma once


#include <cppexpose/plugin/Example.h>

#include <cppexpose/plugin/plugin_api.h>


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
    */
    HelloWorld();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~HelloWorld();

    // Virtual cppexpose::Example interface
    virtual void run() override;
};
