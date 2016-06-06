
#pragma once


#include <string>

#include <cppexpose/reflection/PropertyGroup.h>
#include <cppexpose/reflection/Property.h>

#include "Mood.h"
#include "PropertyExtensions.h"


class MyObject : public cppexpose::PropertyGroup
{
public:
    // Properties
    cppexpose::Property<std::string> String;
    cppexpose::Property<int>         Int;
    cppexpose::Property<float>       Float;
    cppexpose::Property<Mood>        MyMood;


public:
    MyObject(const std::string & name = "Object");
    virtual ~MyObject();

    void print();

    std::string getString() const;
    void setString(const std::string & value);

    int getInt() const;
    void setInt(const int & value);

    float getFloat() const;
    void setFloat(const float & value);

    Mood getMood() const;
    void setMood(const Mood & value);


protected:
    std::string m_string;
    int         m_int;
    float       m_float;
    Mood        m_mood;
};
