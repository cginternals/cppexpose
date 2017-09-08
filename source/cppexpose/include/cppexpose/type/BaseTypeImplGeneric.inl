
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
BaseTypeImplGeneric<T>::BaseTypeImplGeneric()
{
}

template <typename T>
BaseTypeImplGeneric<T>::~BaseTypeImplGeneric()
{
}

template <typename T>
std::string BaseTypeImplGeneric<T>::typeName() const
{
    // Unknown type
    return "unknown";
}

template <typename T>
bool BaseTypeImplGeneric<T>::isNull() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isType() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isArray() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isDynamicArray() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isMap() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isBoolean() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isNumber() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isIntegral() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isUnsigned() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isFloatingPoint() const
{
    // Unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::isString() const
{
    // Unknown type
    return false;
}

template <typename T>
const T & BaseTypeImplGeneric<T>::defaultValue() const
{
    static T value;

    return value;
}

template <typename T>
std::string BaseTypeImplGeneric<T>::toString(const T &) const
{
    // Unsupported for unknown type
    return "";
}

template <typename T>
bool BaseTypeImplGeneric<T>::fromString(T &, const std::string &) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::toBool(const T &) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
bool BaseTypeImplGeneric<T>::fromBool(T &, bool) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
long long BaseTypeImplGeneric<T>::toLongLong(const T &) const
{
    // Unsupported for unknown type
    return 0ll;
}

template <typename T>
bool BaseTypeImplGeneric<T>::fromLongLong(T &, long long) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
unsigned long long BaseTypeImplGeneric<T>::toULongLong(const T &) const
{
    // Unsupported for unknown type
    return 0ull;
}

template <typename T>
bool BaseTypeImplGeneric<T>::fromULongLong(T &, unsigned long long) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
double BaseTypeImplGeneric<T>::toDouble(const T &) const
{
    // Unsupported for unknown type
    return 0.0;
}

template <typename T>
bool BaseTypeImplGeneric<T>::fromDouble(T &, double) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
size_t BaseTypeImplGeneric<T>::numElements(const T &) const
{
    // Unsupported for unknown type
    return 1;
}

template <typename T>
T BaseTypeImplGeneric<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return defaultValue();
    }
}

template <typename T>
void BaseTypeImplGeneric<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void BaseTypeImplGeneric<T>::push(T &, T) const
{
    // Unsupported for unknown type
}

template <typename T>
std::vector<std::string> BaseTypeImplGeneric<T>::keys(const T &) const
{
    // Unsupported for unknown type
    return std::vector<std::string>();
}

template <typename T>
T BaseTypeImplGeneric<T>::getElement(const T &, const std::string &) const
{
    // Unsupported for unknown type
    return this->defaultValue();
}

template <typename T>
void BaseTypeImplGeneric<T>::setElement(T &, const std::string &, T) const
{
    // Unsupported for unknown type
}


} // namespace cppexpose
