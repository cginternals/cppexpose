
#include "HelloWorld.h"

#include <iostream>


CPPEXPOSE_COMPONENT(HelloWorld, cppexpose::Example)


HelloWorld::HelloWorld()
{
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::run()
{
    std::cout << "Hello World!" << std::endl;
}
