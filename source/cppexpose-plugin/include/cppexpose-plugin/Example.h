
#pragma once


#include <cppexpose-plugin/cppexpose-plugin_api.h>


namespace cppexpose_plugin
{


/**
*  @brief
*    Example class used to demonstrate plugins
*/
class CPPEXPOSE_PLUGIN_API Example
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


} // namespace cppexpose_plugin
