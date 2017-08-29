
#pragma once


#include <typeinfo>

#include <cppassist/string/conversion.h>


namespace cppexpose
{


template <typename T>
TypeNumber<T>::TypeNumber()
{
}

template <typename T>
TypeNumber<T>::~TypeNumber()
{
}

template <typename T>
const std::type_info & TypeNumber<T>::typeInfo() const
{
    return typeid(T);
}

template <typename T>
bool TypeNumber<T>::isArray() const
{
    return false;
}

template <typename T>
bool TypeNumber<T>::isDynamicArray() const
{
    return false;
}

template <typename T>
bool TypeNumber<T>::isBoolean() const
{
    return false;
}

template <typename T>
bool TypeNumber<T>::isNumber() const
{
    return true;
}

template <typename T>
bool TypeNumber<T>::isString() const
{
    return false;
}

template <typename T>
std::string TypeNumber<T>::toString(const T & var) const
{
    return cppassist::string::toString<T>(var);
}

template <typename T>
bool TypeNumber<T>::fromString(T & var, const std::string & value) const
{
    var = cppassist::string::fromString<T>(value);
    return true;
}

template <typename T>
bool TypeNumber<T>::toBool(const T & var) const
{
    return static_cast<bool>(var);
}

template <typename T>
bool TypeNumber<T>::fromBool(T & var, bool value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
long long TypeNumber<T>::toLongLong(const T & var) const
{
    return static_cast<long long>(var);
}

template <typename T>
bool TypeNumber<T>::fromLongLong(T & var, long long value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
unsigned long long TypeNumber<T>::toULongLong(const T & var) const
{
    return static_cast<unsigned long long>(var);
}

template <typename T>
bool TypeNumber<T>::fromULongLong(T & var, unsigned long long value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
double TypeNumber<T>::toDouble(const T & var) const
{
    return static_cast<double>(var);
}

template <typename T>
bool TypeNumber<T>::fromDouble(T & var, double value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
size_t TypeNumber<T>::numElements(const T &) const
{
    return 1;
}

template <typename T>
T TypeNumber<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return this->defaultValue();
    }
}

template <typename T>
void TypeNumber<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void TypeNumber<T>::push(T &, T) const
{
}


} // namespace cppexpose
