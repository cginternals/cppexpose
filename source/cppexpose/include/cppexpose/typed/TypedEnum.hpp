
#pragma once


#include <cppexpose/typed/TypedEnum.h>


namespace cppexpose
{


template <typename T>
TypedEnum<T>::TypedEnum()
{
}

template <typename T>
TypedEnum<T>::~TypedEnum()
{
}

template <typename T>
std::string TypedEnum<T>::typeName() const
{
    return "enum";
}

template <typename T>
std::string TypedEnum<T>::toString() const
{
    // [TODO]
    return "";
}

template <typename T>
bool TypedEnum<T>::fromString(const std::string & value)
{
    // [TODO]
    return false;
}

template <typename T>
bool TypedEnum<T>::toBool() const
{
    // [TODO]
    return false;
}

template <typename T>
bool TypedEnum<T>::fromBool(bool value)
{
    // [TODO]
    return false;
}

template <typename T>
long long TypedEnum<T>::toLongLong() const
{
    // [TODO]
    return 0ll;
}

template <typename T>
bool TypedEnum<T>::fromLongLong(long long value)
{
    // [TODO]
    return false;
}

template <typename T>
unsigned long long TypedEnum<T>::toULongLong() const
{
    // [TODO]
    return 0ull;
}

template <typename T>
bool TypedEnum<T>::fromULongLong(unsigned long long value)
{
    // [TODO]
    return false;
}

template <typename T>
double TypedEnum<T>::toDouble() const
{
    // [TODO]
    return 0.0;
}

template <typename T>
bool TypedEnum<T>::fromDouble(double value)
{
    // [TODO]
    return false;
}


} // namespace cppexpose
