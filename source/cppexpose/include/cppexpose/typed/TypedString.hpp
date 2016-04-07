
#pragma once


#include <cppexpose/typed/TypedString.h>

#include <cppexpose/base/string_helpers.h>


namespace cppexpose
{


template <typename T>
TypedString<T>::TypedString()
{
}

template <typename T>
TypedString<T>::~TypedString()
{
}

template <typename T>
std::string TypedString<T>::typeName() const
{
    return "string";
}

template <typename T>
bool TypedString<T>::isString() const
{
    return true;
}

template <typename T>
std::string TypedString<T>::toString() const
{
    return this->value();
}

template <typename T>
bool TypedString<T>::fromString(const std::string & value)
{
    this->setValue(value);
    return true;
}

template <typename T>
bool TypedString<T>::toBool() const
{
    return (this->value() == "true");
}

template <typename T>
bool TypedString<T>::fromBool(bool value)
{
    this->setValue(value ? "true" : "false");
    return true;
}

template <typename T>
long long TypedString<T>::toLongLong() const
{
    return helper::fromString<long long>(this->value());
}

template <typename T>
bool TypedString<T>::fromLongLong(long long value)
{
    std::string str = helper::toString<long long>(value);

    if (str != "") {
        this->setValue(str);
        return true;
    } else {
        return false;
    }
}

template <typename T>
unsigned long long TypedString<T>::toULongLong() const
{
    return helper::fromString<unsigned long long>(this->value());
}

template <typename T>
bool TypedString<T>::fromULongLong(unsigned long long value)
{
    std::string str = helper::toString<unsigned long long>(value);

    if (str != "") {
        this->setValue(str);
        return true;
    } else {
        return false;
    }
}

template <typename T>
double TypedString<T>::toDouble() const
{
    return helper::fromString<double>(this->value());
}

template <typename T>
bool TypedString<T>::fromDouble(double value)
{
    std::string str = helper::toString<double>(value);

    if (str != "") {
        this->setValue(str);
        return true;
    } else {
        return false;
    }
}


} // namespace cppexpose
