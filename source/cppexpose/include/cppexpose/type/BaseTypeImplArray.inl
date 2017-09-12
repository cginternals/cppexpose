
#pragma once


#include <typeinfo>
#include <sstream>

#include <cppassist/string/manipulation.h>


namespace cppexpose
{


template <typename T>
class BaseType;


template <typename T, typename ET, size_t SIZE>
BaseTypeImplArray<T, ET, SIZE>::BaseTypeImplArray()
{
}

template <typename T, typename ET, size_t SIZE>
BaseTypeImplArray<T, ET, SIZE>::~BaseTypeImplArray()
{
}

template <typename T, typename ET, size_t SIZE>
const std::string & BaseTypeImplArray<T, ET, SIZE>::typeName() const
{
    static BaseType<ET> subType;
    static const auto name = std::string("array<") + subType.typeName() + ", " + std::to_string(SIZE) + ">";

    return name;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isNull() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isType() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isArray() const
{
    return true;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isDynamicArray() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isMap() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isBoolean() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isNumber() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isIntegral() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isUnsigned() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isFloatingPoint() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::isString() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
const T & BaseTypeImplArray<T, ET, SIZE>::defaultValue() const
{
    static T value;

    return value;
}

template <typename T, typename ET, size_t SIZE>
std::string BaseTypeImplArray<T, ET, SIZE>::toString(const T & var) const
{
    BaseType<ET> subType;

    std::string str = "(";

    for (size_t i=0; i<SIZE; i++)
    {
        if (i > 0) str += ", ";
        ET value = getElement(var, i);
        str += subType.toString(value);
    }

    str += ")";

    return str;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::fromString(T & var, const std::string & value) const
{
    BaseType<ET> subType;

    std::vector<std::string> elementStrings = cppassist::string::parseArray(value, SIZE);

    if (elementStrings.size() != SIZE) {
        return false;
    }

    for (size_t i=0; i<SIZE; i++)
    {
        ET value;

        if (!subType.fromString(value, elementStrings[i])) {
            return false;
        }

        setElement(var, i, value);
    }

    return true;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::toBool(const T &) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::fromBool(T &, bool) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
long long BaseTypeImplArray<T, ET, SIZE>::toLongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::fromLongLong(T &, long long) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
unsigned long long BaseTypeImplArray<T, ET, SIZE>::toULongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::fromULongLong(T &, unsigned long long) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
double BaseTypeImplArray<T, ET, SIZE>::toDouble(const T &) const
{
    return 0.0;
}

template <typename T, typename ET, size_t SIZE>
bool BaseTypeImplArray<T, ET, SIZE>::fromDouble(T &, double) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
size_t BaseTypeImplArray<T, ET, SIZE>::numElements(const T &) const
{
    return SIZE;
}

template <typename T, typename ET, size_t SIZE>
ET BaseTypeImplArray<T, ET, SIZE>::getElement(const T & var, size_t i) const
{
    return var[i];
}

template <typename T, typename ET, size_t SIZE>
void BaseTypeImplArray<T, ET, SIZE>::setElement(T & var, size_t i, ET value) const
{
    var[i] = value;
}

template <typename T, typename ET, size_t SIZE>
void BaseTypeImplArray<T, ET, SIZE>::push(T &, ET) const
{
    // Not supported for static arrays
}

template <typename T, typename ET, size_t SIZE>
std::vector<std::string> BaseTypeImplArray<T, ET, SIZE>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T, typename ET, size_t SIZE>
ET BaseTypeImplArray<T, ET, SIZE>::getElement(const T &, const std::string &) const
{
    BaseType<ET> subType;
    return subType.defaultValue();
}

template <typename T, typename ET, size_t SIZE>
void BaseTypeImplArray<T, ET, SIZE>::setElement(T &, const std::string &, ET) const
{
}


} // namespace cppexpose
