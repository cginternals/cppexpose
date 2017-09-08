
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
BaseTypeImplString<T>::BaseTypeImplString()
{
}

template <typename T>
BaseTypeImplString<T>::~BaseTypeImplString()
{
}

template <typename T>
std::string BaseTypeImplString<T>::typeName() const
{
    return "string";
}

template <typename T>
bool BaseTypeImplString<T>::isNull() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isType() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isArray() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isDynamicArray() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isMap() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isBoolean() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isNumber() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isIntegral() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
bool BaseTypeImplString<T>::isString() const
{
    return true;
}

template <typename T>
const T & BaseTypeImplString<T>::defaultValue() const
{
    static T value = "";

    return value;
}

template <typename T>
std::string BaseTypeImplString<T>::toString(const T & var) const
{
    return var;
}

template <typename T>
bool BaseTypeImplString<T>::fromString(T & var, const std::string & value) const
{
    var = value;
    return true;
}

template <typename T>
bool BaseTypeImplString<T>::toBool(const T & var) const
{
    return (var == "true");
}

template <typename T>
bool BaseTypeImplString<T>::fromBool(T & var, bool value) const
{
    var = (value ? "true" : "false");
    return true;
}

///-->

template <typename T>
long long BaseTypeImplString<T>::toLongLong(const T & var) const
{
    return cppassist::string::fromString<long long>(var);
}

template <typename T>
bool BaseTypeImplString<T>::fromLongLong(T & var, long long value) const
{
    std::string str = cppassist::string::toString<long long>(value);

    if (str != "") {
        var = str;
        return true;
    } else {
        return false;
    }
}

template <typename T>
unsigned long long BaseTypeImplString<T>::toULongLong(const T & var) const
{
    return cppassist::string::fromString<unsigned long long>(var);
}

template <typename T>
bool BaseTypeImplString<T>::fromULongLong(T & var, unsigned long long value) const
{
    std::string str = cppassist::string::toString<unsigned long long>(value);

    if (str != "") {
        var = str;
        return true;
    } else {
        return false;
    }
}

template <typename T>
double BaseTypeImplString<T>::toDouble(const T & var) const
{
    return cppassist::string::fromString<double>(var);
}

template <typename T>
bool BaseTypeImplString<T>::fromDouble(T & var, double value) const
{
    std::string str = cppassist::string::toString<double>(value);

    if (str != "") {
        var = str;
        return true;
    } else {
        return false;
    }
}

template <typename T>
size_t BaseTypeImplString<T>::numElements(const T &) const
{
    return 1;
}

template <typename T>
T BaseTypeImplString<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return defaultValue();
    }
}

template <typename T>
void BaseTypeImplString<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void BaseTypeImplString<T>::push(T &, T) const
{
}

template <typename T>
std::vector<std::string> BaseTypeImplString<T>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T>
T BaseTypeImplString<T>::getElement(const T &, const std::string &) const
{
    return this->defaultValue();
}

template <typename T>
void BaseTypeImplString<T>::setElement(T &, const std::string &, T) const
{
}


} // namespace cppexpose
