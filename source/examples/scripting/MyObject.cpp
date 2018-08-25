
#include "MyObject.h"

#include <iostream>


using namespace cppexpose;


MyObject::MyObject()
: String(this, "string", "Hallo")
, Int   (this, "int", 100)
, Float (this, "float", 23.42f)
{
    addFunction("print",        this, &MyObject::print);
    addFunction("test",         this, &MyObject::test);
    addFunction("setFunction",  this, &MyObject::setFunction);
    addFunction("callFunction", this, &MyObject::callFunction);
}

MyObject::~MyObject()
{
}

void MyObject::print(const Variant & value)
{
    std::cout << ":: " << value.toString() << std::endl;
}

void MyObject::test(int a, float b)
{
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
}

void MyObject::setFunction(const Variant & func)
{
    if (func.type() == VarType::Function) {
        // [TODO] This will most probably not work yet
        std::cout << "Setting function." << std::endl;
        m_func = func.convert<Function>();
    } else {
        std::cout << "Parameter is not a function." << std::endl;
    }
}

void MyObject::callFunction()
{
    m_func.call({Variant::fromValue<cppexpose::Object *>(this)});
}
