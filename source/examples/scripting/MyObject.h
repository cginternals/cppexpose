
#pragma once


#include <string>

#include <cppexpose/Object.h>
#include <cppexpose/Function.h>
#include <cppexpose/Var.h>
#include <cppexpose/Variant.h>

#include "MyObject.h"


class MyObject : public cppexpose::Object
{
public:
    // Signal
    cppexpose::Signal<int> numberFound;

    // Properties
    cppexpose::Var<std::string> String;
    cppexpose::Var<int>         Int;
    cppexpose::Var<float>       Float;


public:
    MyObject();
    virtual ~MyObject();


protected:
    void print(const cppexpose::Variant & value);
    void test(int a, float b);
    void setFunction(const cppexpose::Variant & func);
    void callFunction();
    void emitSignal();
    void connect(const std::string & name, const cppexpose::Variant & func);


protected:
    cppexpose::Function m_func;
};
