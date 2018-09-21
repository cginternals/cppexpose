
#include "MyObject.h"

#include <iostream>


using namespace cppexpose;


MyObject::MyObject()
: Object()
, String  (this, "string", "Hello")
, Int     (this, "int"   , 1)
, Float   (this, "float",  0.1f)
, MyMood  (this, "mood",   Mood::Sad)
, Array   (this, "array")
, Pointer (this, "pointer", nullptr)
, Filename(this, "filename", "")
{
}

MyObject::~MyObject()
{
}

void MyObject::print()
{
    /*
    std::cout << "string = '" << String.value() << "'" << std::endl;
    std::cout << "int    = "  << Int.value() << std::endl;
    std::cout << "float  = "  << Float.value() << std::endl;
    std::cout << "mood   = "  << MyMood.convert<int>() << " (" << MyMood.convert<std::string>() << ")" << std::endl;
    std::cout << std::endl;
    */
}
