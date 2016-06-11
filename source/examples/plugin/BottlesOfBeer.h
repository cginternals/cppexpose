
#pragma once


#include <cppexpose/plugin/Example.h>
#include <cppexpose/plugin/plugin_api.h>

#include <cppexpose/cppexpose-version.h>


/**
*  @brief
*    99 bottles of beer example
*/
class BottlesOfBeer : public cppexpose::Example
{
public:
    CPPEXPOSE_DECLARE_COMPONENT(
        BottlesOfBeer, cppexpose::Example,
        "", // Tags
        "", // Icon
        "", // Annotations
        "Drinks and counts",
        CPPEXPOSE_AUTHOR_ORGANIZATION,
        "v1.0.0"
    )


public:
    /**
    *  @brief
    *    Constructor
    */
    BottlesOfBeer();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~BottlesOfBeer();

    // Virtual cppexpose::Example interface
    virtual void run() override;
};
