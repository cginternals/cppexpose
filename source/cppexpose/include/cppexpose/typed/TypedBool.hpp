
#pragma once


#include <cppexpose/typed/TypedBool.h>


namespace cppexpose
{


template <typename T>
TypedBool<T>::TypedBool()
{
}

template <typename T>
TypedBool<T>::~TypedBool()
{
}

template <typename T>
std::string TypedBool<T>::typeName() const
{
    return "bool";
}

template <typename T>
bool TypedBool<T>::isBool() const
{
    return true;
}

template <typename T>
std::string TypedBool<T>::toString() const
{
    return this->value() ? "true" : "false"; 
}

template <typename T>
bool TypedBool<T>::fromString(const std::string & value)
{
    this->setValue(value == "true");
    return true;
}

template <typename T>
bool TypedBool<T>::toBool() const
{
    return this->value();
}

template <typename T>
bool TypedBool<T>::fromBool(bool value)
{
    this->setValue(value);
    return true;
}

template <typename T>
long long TypedBool<T>::toLongLong() const
{
    return this->value() ? 1ll : 0ll;
}

template <typename T>
bool TypedBool<T>::fromLongLong(long long value)
{
    this->setValue((bool)value);
    return true;
}

template <typename T>
unsigned long long TypedBool<T>::toULongLong() const
{
    return this->value() ? 1ull : 0ull;
}

template <typename T>
bool TypedBool<T>::fromULongLong(unsigned long long value)
{
    this->setValue((bool)value);
    return true;
}

template <typename T>
double TypedBool<T>::toDouble() const
{
    return this->value() ? 1.0 : 0.0;
}

template <typename T>
bool TypedBool<T>::fromDouble(double value)
{
    this->setValue((bool)value);
    return true;
}


} // namespace cppexpose
