
#include "BottlesOfBeer.h"

#include <iostream>

#include <cppassist/string/conversion.h>

#include <cppexpose/cppexpose-version.h>


CPPEXPOSE_COMPONENT(BottlesOfBeer, cppexpose::Example)


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
        std::cout << cppassist::string::toString<int>(i) << " bottles of beer ..." << std::endl;
    }
}
