
#pragma once


#include <cppassist/string/manipulation.h>


namespace cppexpose
{


template <typename T>
class BaseType;


template <typename T, typename ET>
BaseTypeImplMap<T, ET>::BaseTypeImplMap()
{
}

template <typename T, typename ET>
BaseTypeImplMap<T, ET>::~BaseTypeImplMap()
{
}

template <typename T, typename ET>
const std::string & BaseTypeImplMap<T, ET>::typeName() const
{
    static BaseType<ET> subType;
    static const auto name = std::string("map<string, ") + subType.typeName() + ">";

    return name;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isNull() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isType() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isArray() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isDynamicArray() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isMap() const
{
    return true;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isBoolean() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isNumber() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isIntegral() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isUnsigned() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isFloatingPoint() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::isString() const
{
    return false;
}

template <typename T, typename ET>
const T & BaseTypeImplMap<T, ET>::defaultValue() const
{
    static T value;

    return value;
}

template <typename T, typename ET>
std::string BaseTypeImplMap<T, ET>::toString(const T &) const
{
    // Not implemented
    return "";
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::fromString(T &, const std::string &) const
{
    // Not implemented
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::toBool(const T &) const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::fromBool(T &, bool) const
{
    return false;
}

template <typename T, typename ET>
long long BaseTypeImplMap<T, ET>::toLongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::fromLongLong(T &, long long) const
{
    return false;
}

template <typename T, typename ET>
unsigned long long BaseTypeImplMap<T, ET>::toULongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::fromULongLong(T &, unsigned long long) const
{
    return false;
}

template <typename T, typename ET>
double BaseTypeImplMap<T, ET>::toDouble(const T &) const
{
    return 0.0;
}

template <typename T, typename ET>
bool BaseTypeImplMap<T, ET>::fromDouble(T &, double) const
{
    return false;
}

template <typename T, typename ET>
size_t BaseTypeImplMap<T, ET>::numElements(const T &) const
{
    return 1;
}

template <typename T, typename ET>
ET BaseTypeImplMap<T, ET>::getElement(const T &, size_t) const
{
    BaseType<ET> subType;
    return subType.defaultValue();
}

template <typename T, typename ET>
void BaseTypeImplMap<T, ET>::setElement(T &, size_t, ET) const
{
}

template <typename T, typename ET>
void BaseTypeImplMap<T, ET>::push(T &, ET) const
{
}

template <typename T, typename ET>
std::vector<std::string> BaseTypeImplMap<T, ET>::keys(const T & var) const
{
    std::vector<std::string> keys;

    for (auto it : var) {
        keys.push_back(it.first);
    }

    return keys;
}

template <typename T, typename ET>
ET BaseTypeImplMap<T, ET>::getElement(const T & var, const std::string & key) const
{
    auto it = var.find(key);

    if (it != var.end()) {
        return it->second;
    }

    else {
        BaseType<ET> subType;
        return subType.defaultValue();
    }
}

template <typename T, typename ET>
void BaseTypeImplMap<T, ET>::setElement(T & var, const std::string & key, ET value) const
{
    var[key] = value;
}


} // namespace cppexpose
