
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
TypeGeneric<T>::TypeGeneric()
{
}

template <typename T>
TypeGeneric<T>::~TypeGeneric()
{
}

template <typename T>
const std::type_info & TypeGeneric<T>::typeInfo() const
{
    return typeid(T);
}

template <typename T>
std::string TypeGeneric<T>::typeName() const
{
    // Unknown type
    return "unknown";
}

template <typename T>
bool TypeGeneric<T>::isNull() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isArray() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isDynamicArray() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isMap() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isBoolean() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isNumber() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isIntegral() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isUnsigned() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isFloatingPoint() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isString() const
{
    // Unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::isType() const
{
    // Unknown type
    return false;
}

template <typename T>
const T & TypeGeneric<T>::defaultValue() const
{
    static T value;

    return value;
}

template <typename T>
std::string TypeGeneric<T>::toString(const T &) const
{
    // Unsupported for unknown type
    return "";
}

template <typename T>
bool TypeGeneric<T>::fromString(T &, const std::string &) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::toBool(const T &) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
bool TypeGeneric<T>::fromBool(T &, bool) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
long long TypeGeneric<T>::toLongLong(const T &) const
{
    // Unsupported for unknown type
    return 0ll;
}

template <typename T>
bool TypeGeneric<T>::fromLongLong(T &, long long) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
unsigned long long TypeGeneric<T>::toULongLong(const T &) const
{
    // Unsupported for unknown type
    return 0ull;
}

template <typename T>
bool TypeGeneric<T>::fromULongLong(T &, unsigned long long) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
double TypeGeneric<T>::toDouble(const T &) const
{
    // Unsupported for unknown type
    return 0.0;
}

template <typename T>
bool TypeGeneric<T>::fromDouble(T &, double) const
{
    // Unsupported for unknown type
    return false;
}

template <typename T>
size_t TypeGeneric<T>::numElements(const T &) const
{
    // Unsupported for unknown type
    return 1;
}

template <typename T>
T TypeGeneric<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return defaultValue();
    }
}

template <typename T>
void TypeGeneric<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void TypeGeneric<T>::push(T &, T) const
{
    // Unsupported for unknown type
}

template <typename T>
std::vector<std::string> TypeGeneric<T>::keys(const T &) const
{
    // Unsupported for unknown type
    return std::vector<std::string>();
}

template <typename T>
T TypeGeneric<T>::getElement(const T &, const std::string &) const
{
    // Unsupported for unknown type
    return this->defaultValue();
}

template <typename T>
void TypeGeneric<T>::setElement(T &, const std::string &, T) const
{
    // Unsupported for unknown type
}


} // namespace cppexpose
