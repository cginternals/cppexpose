
#include <iostream>

#include <cppexpose/plugin/plugin_api.h>

#include "HelloWorld.h"


CPPEXPOSE_PLUGIN_LIBRARY

    CPPEXPOSE_PLUGIN_LIBRARY_INIT
    {
        std::cout << "initializing example-plugins" << std::endl;
    }

    CPPEXPOSE_PLUGIN_LIBRARY_DEINIT
    {
        std::cout << "de-initializing example-plugins" << std::endl;
    }

CPPEXPOSE_PLUGIN_LIBRARY_END
