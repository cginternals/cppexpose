
#pragma once


#include <cppexpose/plugin/Example.h>
#include <cppexpose/plugin/plugin_api.h>

#include <cppexpose/cppexpose-version.h>


/**
*  @brief
*    Hello world example
*/
class HelloWorld : public cppexpose::Example
{
public:
    CPPEXPOSE_DECLARE_COMPONENT(
        HelloWorld, cppexpose::Example,
        "", // Tags
        "", // Icon
        "", // Annotations
        "Prints 'Hello World' to the console",
        CPPEXPOSE_AUTHOR_ORGANIZATION,
        "v1.0.0"
    )


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
