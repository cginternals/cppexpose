
#pragma once


#include <cppexpose/typed/TypedVariant.hh>

#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


template <typename T, typename BASE>
TypedVariant<T, BASE>::TypedVariant()
{
}

template <typename T, typename BASE>
TypedVariant<T, BASE>::~TypedVariant()
{
}

template <typename T, typename BASE>
std::string TypedVariant<T, BASE>::typeName() const
{
    return "variant";
}

template <typename T, typename BASE>
bool TypedVariant<T, BASE>::isVariant() const
{
    return true;
}

template <typename T, typename BASE>
std::string TypedVariant<T, BASE>::toString() const
{
    return this->value().toString();
}

template <typename T, typename BASE>
bool TypedVariant<T, BASE>::fromString(const std::string & value)
{
    this->setValue(Variant(value));
    return true;
}

template <typename T, typename BASE>
bool TypedVariant<T, BASE>::toBool() const
{
    return this->value().toBool();
}

template <typename T, typename BASE>
bool TypedVariant<T, BASE>::fromBool(bool value)
{
    this->setValue(Variant(value));
    return true;
}

template <typename T, typename BASE>
long long TypedVariant<T, BASE>::toLongLong() const
{
    return this->value().toLongLong();
}

template <typename T, typename BASE>
bool TypedVariant<T, BASE>::fromLongLong(long long value)
{
    this->setValue(Variant(value));
    return true;
}

template <typename T, typename BASE>
unsigned long long TypedVariant<T, BASE>::toULongLong() const
{
    return this->value().toULongLong();
}

template <typename T, typename BASE>
bool TypedVariant<T, BASE>::fromULongLong(unsigned long long value)
{
    this->setValue(Variant(value));
    return true;
}

template <typename T, typename BASE>
double TypedVariant<T, BASE>::toDouble() const
{
    return this->value().toDouble();
}

template <typename T, typename BASE>
bool TypedVariant<T, BASE>::fromDouble(double value)
{
    this->setValue(Variant(value));
    return true;
}


} // namespace cppexpose
