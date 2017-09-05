
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
TypeBoolean<T>::TypeBoolean()
{
}

template <typename T>
TypeBoolean<T>::~TypeBoolean()
{
}

template <typename T>
const std::type_info & TypeBoolean<T>::typeInfo() const
{
    return typeid(T);
}

template <typename T>
std::string TypeBoolean<T>::typeName() const
{
    return "bool";
}

template <typename T>
bool TypeBoolean<T>::isArray() const
{
    return false;
}

template <typename T>
bool TypeBoolean<T>::isDynamicArray() const
{
    return false;
}

template <typename T>
bool TypeBoolean<T>::isMap() const
{
    return false;
}

template <typename T>
bool TypeBoolean<T>::isBoolean() const
{
    return true;
}

template <typename T>
bool TypeBoolean<T>::isNumber() const
{
    return false;
}

template <typename T>
bool TypeBoolean<T>::isIntegral() const
{
    return false;
}

template <typename T>
bool TypeBoolean<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool TypeBoolean<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
bool TypeBoolean<T>::isString() const
{
    return false;
}

template <typename T>
bool TypeBoolean<T>::isType() const
{
    return false;
}

template <typename T>
const T & TypeBoolean<T>::defaultValue() const
{
    static T value = false;

    return value;
}

template <typename T>
std::string TypeBoolean<T>::toString(const T & var) const
{
    return static_cast<bool>(var) ? "true" : "false";
}

template <typename T>
bool TypeBoolean<T>::fromString(T & var, const std::string & value) const
{
    var = (value == "true");
    return true;
}

template <typename T>
bool TypeBoolean<T>::toBool(const T & var) const
{
    return static_cast<bool>(var);
}

template <typename T>
bool TypeBoolean<T>::fromBool(T & var, bool value) const
{
    var = value;
    return true;
}

template <typename T>
long long TypeBoolean<T>::toLongLong(const T & var) const
{
    return static_cast<bool>(var) ? 1ll : 0ll;
}

template <typename T>
bool TypeBoolean<T>::fromLongLong(T & var, long long value) const
{
    var = static_cast<bool>(value);
    return true;
}

template <typename T>
unsigned long long TypeBoolean<T>::toULongLong(const T & var) const
{
    return static_cast<bool>(var) ? 1ull : 0ull;
}

template <typename T>
bool TypeBoolean<T>::fromULongLong(T & var, unsigned long long value) const
{
    var = static_cast<bool>(value);
    return true;
}

template <typename T>
double TypeBoolean<T>::toDouble(const T & var) const
{
    return static_cast<bool>(var) ? 1.0 : 0.0;
}

template <typename T>
bool TypeBoolean<T>::fromDouble(T & var, double value) const
{
    var = static_cast<bool>(value);
    return true;
}

template <typename T>
size_t TypeBoolean<T>::numElements(const T &) const
{
    return 1;
}

template <typename T>
T TypeBoolean<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return defaultValue();
    }
}

template <typename T>
void TypeBoolean<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void TypeBoolean<T>::push(T &, T) const
{
}

template <typename T>
std::vector<std::string> TypeBoolean<T>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T>
T TypeBoolean<T>::getElement(const T &, const std::string &) const
{
    return this->defaultValue();
}

template <typename T>
void TypeBoolean<T>::setElement(T &, const std::string &, T) const
{
}


} // namespace cppexpose
