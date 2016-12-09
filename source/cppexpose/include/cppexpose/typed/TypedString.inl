
#pragma once


#include <cppexpose/base/string_helpers.h>


namespace cppexpose
{


template <typename T, typename BASE>
TypedString<T, BASE>::TypedString()
{
}

template <typename T, typename BASE>
TypedString<T, BASE>::~TypedString()
{
}

template <typename T, typename BASE>
std::string TypedString<T, BASE>::typeName() const
{
    return "string";
}

template <typename T, typename BASE>
bool TypedString<T, BASE>::isString() const
{
    return true;
}

template <typename T, typename BASE>
std::string TypedString<T, BASE>::toString() const
{
    return this->value();
}

template <typename T, typename BASE>
bool TypedString<T, BASE>::fromString(const std::string & value)
{
    this->setValue(value);
    return true;
}

template <typename T, typename BASE>
bool TypedString<T, BASE>::toBool() const
{
    return (this->value() == "true");
}

template <typename T, typename BASE>
bool TypedString<T, BASE>::fromBool(bool value)
{
    this->setValue(value ? "true" : "false");
    return true;
}

template <typename T, typename BASE>
long long TypedString<T, BASE>::toLongLong() const
{
    return helper::fromString<long long>(this->value());
}

template <typename T, typename BASE>
bool TypedString<T, BASE>::fromLongLong(long long value)
{
    std::string str = helper::toString<long long>(value);

    if (str != "") {
        this->setValue(str);
        return true;
    } else {
        return false;
    }
}

template <typename T, typename BASE>
unsigned long long TypedString<T, BASE>::toULongLong() const
{
    return helper::fromString<unsigned long long>(this->value());
}

template <typename T, typename BASE>
bool TypedString<T, BASE>::fromULongLong(unsigned long long value)
{
    std::string str = helper::toString<unsigned long long>(value);

    if (str != "") {
        this->setValue(str);
        return true;
    } else {
        return false;
    }
}

template <typename T, typename BASE>
double TypedString<T, BASE>::toDouble() const
{
    return helper::fromString<double>(this->value());
}

template <typename T, typename BASE>
bool TypedString<T, BASE>::fromDouble(double value)
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
