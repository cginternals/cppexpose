
#pragma once


#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Example class used to demonstrate plugins
*/
class CPPEXPOSE_API Example
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Example();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Example();

    /**
    *  @brief
    *    Run the example program
    */
    virtual void run() = 0;
};


} // namespace cppexpose
