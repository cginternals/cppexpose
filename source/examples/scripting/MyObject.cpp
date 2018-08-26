
#include "MyObject.h"

#include <iostream>


using namespace cppexpose;


MyObject::MyObject()
: numberFound(this, "numberFound")
, String(this, "string", "Hallo")
, Int   (this, "int", 100)
, Float (this, "float", 23.42f)
{
    addFunction("print",        this, &MyObject::print);
    addFunction("test",         this, &MyObject::test);
    addFunction("setFunction",  this, &MyObject::setFunction);
    addFunction("callFunction", this, &MyObject::callFunction);
    addFunction("emitSignal",   this, &MyObject::emitSignal);
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

void MyObject::setFunction(const Function & func)
{
    // Example usage:
    //   script.obj.setFunction(function(){print('hallo!');});
    //   script.obj.callFunction();

    // Save function
    std::cout << "Setting function." << std::endl;
    m_func = func;
}

void MyObject::callFunction()
{
    m_func.call({Variant::fromValue<cppexpose::Object *>(this)});
}

void MyObject::emitSignal()
{
    // Example usage:
    //   print(script.obj.signals());
    //   script.obj.connect('numberFound', function(num){print('Number: ' + num);});
    //   script.obj.emitSignal();

    numberFound(42);
}
