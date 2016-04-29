
#pragma once


#include <cppexpose/typed/TypedVariant.hh>

#include <cppexpose/variant/Variant.h>


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
    return this->value().toString();
}

template <typename T>
bool TypedVariant<T>::fromString(const std::string & value)
{
    this->setValue(Variant(value));
    return true;
}

template <typename T>
bool TypedVariant<T>::toBool() const
{
    return this->value().toBool();
}

template <typename T>
bool TypedVariant<T>::fromBool(bool value)
{
    this->setValue(Variant(value));
    return true;
}

template <typename T>
long long TypedVariant<T>::toLongLong() const
{
    return this->value().toLongLong();
}

template <typename T>
bool TypedVariant<T>::fromLongLong(long long value)
{
    this->setValue(Variant(value));
    return true;
}

template <typename T>
unsigned long long TypedVariant<T>::toULongLong() const
{
    return this->value().toULongLong();
}

template <typename T>
bool TypedVariant<T>::fromULongLong(unsigned long long value)
{
    this->setValue(Variant(value));
    return true;
}

template <typename T>
double TypedVariant<T>::toDouble() const
{
    return this->value().toDouble();
}

template <typename T>
bool TypedVariant<T>::fromDouble(double value)
{
    this->setValue(Variant(value));
    return true;
}


} // namespace cppexpose
