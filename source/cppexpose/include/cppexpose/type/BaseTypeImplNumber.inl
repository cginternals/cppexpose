
#pragma once


#include <typeinfo>
#include <limits>

#include <cppassist/string/conversion.h>


namespace cppexpose
{


template <typename T>
BaseTypeImplNumber<T>::BaseTypeImplNumber()
: m_minimumValue(std::numeric_limits<T>::lowest())
, m_maximumValue(std::numeric_limits<T>::max())
{
}

template <typename T>
BaseTypeImplNumber<T>::~BaseTypeImplNumber()
{
}

template <typename T>
bool BaseTypeImplNumber<T>::isNull() const
{
    return false;
}

template <typename T>
bool BaseTypeImplNumber<T>::isType() const
{
    return false;
}

template <typename T>
bool BaseTypeImplNumber<T>::isArray() const
{
    return false;
}

template <typename T>
bool BaseTypeImplNumber<T>::isDynamicArray() const
{
    return false;
}

template <typename T>
bool BaseTypeImplNumber<T>::isMap() const
{
    return false;
}

template <typename T>
bool BaseTypeImplNumber<T>::isBoolean() const
{
    return false;
}

template <typename T>
bool BaseTypeImplNumber<T>::isNumber() const
{
    return true;
}

template <typename T>
bool BaseTypeImplNumber<T>::isString() const
{
    return false;
}

template <typename T>
const T & BaseTypeImplNumber<T>::minimumValue() const
{
    return m_minimumValue;
}

template <typename T>
void BaseTypeImplNumber<T>::setMinimumValue(const T & value)
{
    m_minimumValue = value;
}

template <typename T>
const T & BaseTypeImplNumber<T>::maximumValue() const
{
    return m_maximumValue;
}

template <typename T>
void BaseTypeImplNumber<T>::setMaximumValue(const T & value)
{
    m_maximumValue = value;
}

template <typename T>
std::string BaseTypeImplNumber<T>::toString(const T & var) const
{
    return cppassist::string::toString<T>(var);
}

template <typename T>
bool BaseTypeImplNumber<T>::fromString(T & var, const std::string & value) const
{
    var = cppassist::string::fromString<T>(value);
    return true;
}

template <typename T>
bool BaseTypeImplNumber<T>::toBool(const T & var) const
{
    return static_cast<bool>(var);
}

template <typename T>
bool BaseTypeImplNumber<T>::fromBool(T & var, bool value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
long long BaseTypeImplNumber<T>::toLongLong(const T & var) const
{
    return static_cast<long long>(var);
}

template <typename T>
bool BaseTypeImplNumber<T>::fromLongLong(T & var, long long value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
unsigned long long BaseTypeImplNumber<T>::toULongLong(const T & var) const
{
    return static_cast<unsigned long long>(var);
}

template <typename T>
bool BaseTypeImplNumber<T>::fromULongLong(T & var, unsigned long long value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
double BaseTypeImplNumber<T>::toDouble(const T & var) const
{
    return static_cast<double>(var);
}

template <typename T>
bool BaseTypeImplNumber<T>::fromDouble(T & var, double value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
size_t BaseTypeImplNumber<T>::numElements(const T &) const
{
    return 1;
}

template <typename T>
T BaseTypeImplNumber<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return this->defaultValue();
    }
}

template <typename T>
void BaseTypeImplNumber<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void BaseTypeImplNumber<T>::push(T &, T) const
{
}

template <typename T>
std::vector<std::string> BaseTypeImplNumber<T>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T>
T BaseTypeImplNumber<T>::getElement(const T &, const std::string &) const
{
    return this->defaultValue();
}

template <typename T>
void BaseTypeImplNumber<T>::setElement(T &, const std::string &, T) const
{
}


} // namespace cppexpose
