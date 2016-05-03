
#pragma once


#include <cppexpose/plugin/Example.h>

#include <cppexpose/plugin/plugin_api.h>


namespace cpplocate {
    class ModuleInfo;
}


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
    *
    *  @param[in] moduleInfo
    *    Module info of the plugin library containing the component (if any)
    */
    BottlesOfBeer(const cpplocate::ModuleInfo & moduleInfo);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~BottlesOfBeer();

    // Virtual cppexpose::Example interface
    virtual void run() override;
};
