
#pragma once


#include <cppexpose/plugin/Example.h>

#include <cppexpose/plugin/plugin_api.h>


/**
*  @brief
*    99 bottles of beer example
*/
class BottlesOfBeer : public cppexpose::Example
{
CPPEXPOSE_DECLARE_COMPONENT(BottlesOfBeer, cppexpose::Example)


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
