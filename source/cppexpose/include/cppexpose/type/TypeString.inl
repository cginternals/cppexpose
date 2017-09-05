
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
TypeString<T>::TypeString()
{
}

template <typename T>
TypeString<T>::~TypeString()
{
}

template <typename T>
const std::type_info & TypeString<T>::typeInfo() const
{
    return typeid(T);
}

template <typename T>
std::string TypeString<T>::typeName() const
{
    return "string";
}

template <typename T>
bool TypeString<T>::isNull() const
{
    return false;
}

template <typename T>
bool TypeString<T>::isArray() const
{
    return false;
}

template <typename T>
bool TypeString<T>::isDynamicArray() const
{
    return false;
}

template <typename T>
bool TypeString<T>::isMap() const
{
    return false;
}

template <typename T>
bool TypeString<T>::isBoolean() const
{
    return false;
}

template <typename T>
bool TypeString<T>::isNumber() const
{
    return false;
}

template <typename T>
bool TypeString<T>::isIntegral() const
{
    return false;
}

template <typename T>
bool TypeString<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool TypeString<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
bool TypeString<T>::isString() const
{
    return true;
}

template <typename T>
bool TypeString<T>::isType() const
{
    return false;
}

template <typename T>
const T & TypeString<T>::defaultValue() const
{
    static T value = "";

    return value;
}

template <typename T>
std::string TypeString<T>::toString(const T & var) const
{
    return var;
}

template <typename T>
bool TypeString<T>::fromString(T & var, const std::string & value) const
{
    var = value;
    return true;
}

template <typename T>
bool TypeString<T>::toBool(const T & var) const
{
    return (var == "true");
}

template <typename T>
bool TypeString<T>::fromBool(T & var, bool value) const
{
    var = (value ? "true" : "false");
    return true;
}

///-->

template <typename T>
long long TypeString<T>::toLongLong(const T & var) const
{
    return cppassist::string::fromString<long long>(var);
}

template <typename T>
bool TypeString<T>::fromLongLong(T & var, long long value) const
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
unsigned long long TypeString<T>::toULongLong(const T & var) const
{
    return cppassist::string::fromString<unsigned long long>(var);
}

template <typename T>
bool TypeString<T>::fromULongLong(T & var, unsigned long long value) const
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
double TypeString<T>::toDouble(const T & var) const
{
    return cppassist::string::fromString<double>(var);
}

template <typename T>
bool TypeString<T>::fromDouble(T & var, double value) const
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
size_t TypeString<T>::numElements(const T &) const
{
    return 1;
}

template <typename T>
T TypeString<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return defaultValue();
    }
}

template <typename T>
void TypeString<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void TypeString<T>::push(T &, T) const
{
}

template <typename T>
std::vector<std::string> TypeString<T>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T>
T TypeString<T>::getElement(const T &, const std::string &) const
{
    return this->defaultValue();
}

template <typename T>
void TypeString<T>::setElement(T &, const std::string &, T) const
{
}


} // namespace cppexpose
