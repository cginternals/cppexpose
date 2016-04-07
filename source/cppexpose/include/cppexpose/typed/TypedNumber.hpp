
#pragma once


#include <cppexpose/typed/TypedNumber.h>

#include <cppexpose/base/string_helpers.h>


namespace cppexpose
{


template <typename T>
TypedNumber<T>::TypedNumber()
{
}

template <typename T>
TypedNumber<T>::~TypedNumber()
{
}

template <typename T>
bool TypedNumber<T>::isNumber() const
{
    return true;
}

template <typename T>
std::string TypedNumber<T>::toString() const
{
    return helper::toString<T>(this->value());
}

template <typename T>
bool TypedNumber<T>::fromString(const std::string & value)
{
    this->setValue(helper::fromString<T>(value));
    return true;
}

template <typename T>
bool TypedNumber<T>::toBool() const
{
    return (bool)this->value();
}

template <typename T>
bool TypedNumber<T>::fromBool(bool value)
{
    this->setValue((T)value);
    return true;
}

template <typename T>
long long TypedNumber<T>::toLongLong() const
{
    return (long long)this->value();
}

template <typename T>
bool TypedNumber<T>::fromLongLong(long long value)
{
    this->setValue((T)value);
    return true;
}

template <typename T>
unsigned long long TypedNumber<T>::toULongLong() const
{
    return (unsigned long long)this->value();
}

template <typename T>
bool TypedNumber<T>::fromULongLong(unsigned long long value)
{
    this->setValue((T)value);
    return true;
}

template <typename T>
double TypedNumber<T>::toDouble() const
{
    return (double)this->value();
}

template <typename T>
bool TypedNumber<T>::fromDouble(double value)
{
    this->setValue((T)value);
    return true;
}


} // namespace cppexpose
