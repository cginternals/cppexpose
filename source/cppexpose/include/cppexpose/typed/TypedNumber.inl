
#pragma once


#include <cppassist/string/conversion.h>


namespace cppexpose
{


template <typename T, typename BASE>
TypedNumber<T, BASE>::TypedNumber()
{
}

template <typename T, typename BASE>
TypedNumber<T, BASE>::~TypedNumber()
{
}

template <typename T, typename BASE>
bool TypedNumber<T, BASE>::isNumber() const
{
    return true;
}

template <typename T, typename BASE>
std::string TypedNumber<T, BASE>::toString() const
{
    return cppassist::toString<T>(this->value());
}

template <typename T, typename BASE>
bool TypedNumber<T, BASE>::fromString(const std::string & value)
{
    this->setValue(cppassist::fromString<T>(value));
    return true;
}

template <typename T, typename BASE>
bool TypedNumber<T, BASE>::toBool() const
{
    return (bool)this->value();
}

template <typename T, typename BASE>
bool TypedNumber<T, BASE>::fromBool(bool value)
{
    this->setValue((T)value);
    return true;
}

template <typename T, typename BASE>
long long TypedNumber<T, BASE>::toLongLong() const
{
    return (long long)this->value();
}

template <typename T, typename BASE>
bool TypedNumber<T, BASE>::fromLongLong(long long value)
{
    this->setValue((T)value);
    return true;
}

template <typename T, typename BASE>
unsigned long long TypedNumber<T, BASE>::toULongLong() const
{
    return (unsigned long long)this->value();
}

template <typename T, typename BASE>
bool TypedNumber<T, BASE>::fromULongLong(unsigned long long value)
{
    this->setValue((T)value);
    return true;
}

template <typename T, typename BASE>
double TypedNumber<T, BASE>::toDouble() const
{
    return (double)this->value();
}

template <typename T, typename BASE>
bool TypedNumber<T, BASE>::fromDouble(double value)
{
    this->setValue((T)value);
    return true;
}


} // namespace cppexpose
