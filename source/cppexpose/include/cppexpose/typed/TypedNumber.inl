
#pragma once


#include <cppassist/string/conversion.h>


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4800) // 'type': forcing value to bool 'true' or 'false'
#endif


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
    return cppassist::string::toString<T>(this->value());
}

template <typename T, typename BASE>
bool TypedNumber<T, BASE>::fromString(const std::string & value)
{
    this->setValue(cppassist::string::fromString<T>(value));
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


#ifdef _MSC_VER
#pragma warning(pop)
#endif
