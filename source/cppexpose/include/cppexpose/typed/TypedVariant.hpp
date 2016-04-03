
#pragma once


#include <cppexpose/typed/TypedVariant.h>


namespace cppexpose
{


template <typename T>
TypedVariant<T>::TypedVariant()
{
}

template <typename T>
TypedVariant<T>::~TypedVariant()
{
}

template <typename T>
std::string TypedVariant<T>::typeName() const
{
    return "variant";
}

template <typename T>
bool TypedVariant<T>::isVariant() const
{
    return true;
}

template <typename T>
std::string TypedVariant<T>::toString() const
{
    // [TODO]
    return "";
}

template <typename T>
bool TypedVariant<T>::fromString(const std::string & value)
{
    // [TODO]
    return false;
}

template <typename T>
bool TypedVariant<T>::toBool() const
{
    // [TODO]
    return false;
}

template <typename T>
bool TypedVariant<T>::fromBool(bool value)
{
    // [TODO]
    return false;
}

template <typename T>
long long TypedVariant<T>::toLongLong() const
{
    // [TODO]
    return 0ll;
}

template <typename T>
bool TypedVariant<T>::fromLongLong(long long value)
{
    // [TODO]
    return false;
}

template <typename T>
unsigned long long TypedVariant<T>::toULongLong() const
{
    // [TODO]
    return 0ull;
}

template <typename T>
bool TypedVariant<T>::fromULongLong(unsigned long long value)
{
    // [TODO]
    return false;
}

template <typename T>
double TypedVariant<T>::toDouble() const
{
    // [TODO]
    return 0.0;
}

template <typename T>
bool TypedVariant<T>::fromDouble(double value)
{
    // [TODO]
    return false;
}


} // namespace cppexpose
