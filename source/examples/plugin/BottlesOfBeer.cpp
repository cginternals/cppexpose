
#include "BottlesOfBeer.h"

#include <iostream>

#include <cppexpose/cppexpose-version.h>
#include <cppexpose/base/string_helpers.h>


CPPEXPOSE_COMPONENT(BottlesOfBeer, cppexpose::Example)


using namespace cppexpose::helper;


BottlesOfBeer::BottlesOfBeer()
{
}

BottlesOfBeer::~BottlesOfBeer()
{
}

void BottlesOfBeer::run()
{
    for (int i=99; i>=0; i--)
    {
        std::cout << toString<int>(i) << " bottles of beer ..." << std::endl;
    }
}
