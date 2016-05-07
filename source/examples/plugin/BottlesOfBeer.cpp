
#include "BottlesOfBeer.h"

#include <iostream>

#include <cppexpose/cppexpose-version.h>
#include <cppexpose/base/string_helpers.h>


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


CPPEXPOSE_COMPONENT(
    BottlesOfBeer, cppexpose::Example,
    "", // Tags
    "", // Icon
    "", // Annotations
    "Drinks and counts",
    CPPEXPOSE_AUTHOR_ORGANIZATION,
    "v1.0.0"
)
