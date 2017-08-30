
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
    return "unknown";
}

template <typename T>
bool TypeGeneric<T>::isArray() const
{
    return false;
}

template <typename T>
bool TypeGeneric<T>::isDynamicArray() const
{
    return false;
}

template <typename T>
bool TypeGeneric<T>::isMap() const
{
    return false;
}

template <typename T>
bool TypeGeneric<T>::isBoolean() const
{
    return false;
}

template <typename T>
bool TypeGeneric<T>::isNumber() const
{
    return false;
}

template <typename T>
bool TypeGeneric<T>::isIntegral() const
{
    return false;
}

template <typename T>
bool TypeGeneric<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool TypeGeneric<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
bool TypeGeneric<T>::isString() const
{
    return false;
}

template <typename T>
const T & TypeGeneric<T>::defaultValue() const
{
    static T value;

    return value;
}

template <typename T>
std::string TypeGeneric<T>::toString(const T & var) const
{
    return var.toString();
}

template <typename T>
bool TypeGeneric<T>::fromString(T & var, const std::string & value) const
{
    return var.fromString(value);
}

template <typename T>
bool TypeGeneric<T>::toBool(const T & var) const
{
    return static_cast<bool>(var);
}

template <typename T>
bool TypeGeneric<T>::fromBool(T & var, bool value) const
{
    var = value;
    return true;
}

template <typename T>
long long TypeGeneric<T>::toLongLong(const T & var) const
{
    return static_cast<long long>(var);
}

template <typename T>
bool TypeGeneric<T>::fromLongLong(T & var, long long value) const
{
    var = value;
    return true;
}

template <typename T>
unsigned long long TypeGeneric<T>::toULongLong(const T & var) const
{
    return static_cast<unsigned long long>(var);
}

template <typename T>
bool TypeGeneric<T>::fromULongLong(T & var, unsigned long long value) const
{
    var = value;
    return true;
}

template <typename T>
double TypeGeneric<T>::toDouble(const T & var) const
{
    return static_cast<double>(var);
}

template <typename T>
bool TypeGeneric<T>::fromDouble(T & var, double value) const
{
    var = value;
    return true;
}

template <typename T>
size_t TypeGeneric<T>::numElements(const T &) const
{
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
}

template <typename T>
std::vector<std::string> TypeGeneric<T>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T>
T TypeGeneric<T>::getElement(const T &, const std::string &) const
{
    return this->defaultValue();
}

template <typename T>
void TypeGeneric<T>::setElement(T &, const std::string &, T) const
{
}


} // namespace cppexpose
