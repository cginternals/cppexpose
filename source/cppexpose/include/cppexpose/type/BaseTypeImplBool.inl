
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
BaseTypeImplBool<T>::BaseTypeImplBool()
{
}

template <typename T>
BaseTypeImplBool<T>::~BaseTypeImplBool()
{
}

template <typename T>
std::string BaseTypeImplBool<T>::typeName() const
{
    return "bool";
}

template <typename T>
bool BaseTypeImplBool<T>::isNull() const
{
    return false;
}

template <typename T>
bool BaseTypeImplBool<T>::isType() const
{
    return false;
}

template <typename T>
bool BaseTypeImplBool<T>::isArray() const
{
    return false;
}

template <typename T>
bool BaseTypeImplBool<T>::isDynamicArray() const
{
    return false;
}

template <typename T>
bool BaseTypeImplBool<T>::isMap() const
{
    return false;
}

template <typename T>
bool BaseTypeImplBool<T>::isBoolean() const
{
    return true;
}

template <typename T>
bool BaseTypeImplBool<T>::isNumber() const
{
    return false;
}

template <typename T>
bool BaseTypeImplBool<T>::isIntegral() const
{
    return false;
}

template <typename T>
bool BaseTypeImplBool<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool BaseTypeImplBool<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
bool BaseTypeImplBool<T>::isString() const
{
    return false;
}

template <typename T>
const T & BaseTypeImplBool<T>::defaultValue() const
{
    static T value = false;

    return value;
}

template <typename T>
std::string BaseTypeImplBool<T>::toString(const T & var) const
{
    return static_cast<bool>(var) ? "true" : "false";
}

template <typename T>
bool BaseTypeImplBool<T>::fromString(T & var, const std::string & value) const
{
    var = (value == "true");
    return true;
}

template <typename T>
bool BaseTypeImplBool<T>::toBool(const T & var) const
{
    return static_cast<bool>(var);
}

template <typename T>
bool BaseTypeImplBool<T>::fromBool(T & var, bool value) const
{
    var = value;
    return true;
}

template <typename T>
long long BaseTypeImplBool<T>::toLongLong(const T & var) const
{
    return static_cast<bool>(var) ? 1ll : 0ll;
}

template <typename T>
bool BaseTypeImplBool<T>::fromLongLong(T & var, long long value) const
{
    var = static_cast<bool>(value);
    return true;
}

template <typename T>
unsigned long long BaseTypeImplBool<T>::toULongLong(const T & var) const
{
    return static_cast<bool>(var) ? 1ull : 0ull;
}

template <typename T>
bool BaseTypeImplBool<T>::fromULongLong(T & var, unsigned long long value) const
{
    var = static_cast<bool>(value);
    return true;
}

template <typename T>
double BaseTypeImplBool<T>::toDouble(const T & var) const
{
    return static_cast<bool>(var) ? 1.0 : 0.0;
}

template <typename T>
bool BaseTypeImplBool<T>::fromDouble(T & var, double value) const
{
    var = static_cast<bool>(value);
    return true;
}

template <typename T>
size_t BaseTypeImplBool<T>::numElements(const T &) const
{
    return 1;
}

template <typename T>
T BaseTypeImplBool<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return defaultValue();
    }
}

template <typename T>
void BaseTypeImplBool<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void BaseTypeImplBool<T>::push(T &, T) const
{
}

template <typename T>
std::vector<std::string> BaseTypeImplBool<T>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T>
T BaseTypeImplBool<T>::getElement(const T &, const std::string &) const
{
    return this->defaultValue();
}

template <typename T>
void BaseTypeImplBool<T>::setElement(T &, const std::string &, T) const
{
}


} // namespace cppexpose
