
#pragma once


#include <string>

#include <cppfs/FilePath.h>

#include <cppexpose/Object.h>
#include <cppexpose/Var.h>

#include "Mood.h"
#include "PropertyExtensions.h"


class MyObject : public cppexpose::Object
{
public:
    // Properties
    cppexpose::Var<std::string>        String;
    cppexpose::Var<int>                Int;
    cppexpose::Var<float>              Float;
    cppexpose::Var<Mood>               MyMood;
    cppexpose::Var<std::array<int, 3>> Array;
    cppexpose::Var<void *>             Pointer;
    cppexpose::Var<cppfs::FilePath>    Filename;

public:
    MyObject();
    virtual ~MyObject();

    void print();
};
