
#pragma once


#include <typeinfo>

#include <cppassist/string/manipulation.h>


namespace cppexpose
{


template <typename T>
class BaseType;


template <typename T, typename ET>
BaseTypeImplVector<T, ET>::BaseTypeImplVector()
{
}

template <typename T, typename ET>
BaseTypeImplVector<T, ET>::~BaseTypeImplVector()
{
}

template <typename T, typename ET>
const std::string & BaseTypeImplVector<T, ET>::typeName() const
{
    static BaseType<ET> subType;
    static const auto name = std::string("vector<") + subType.typeName() + ">";

    return name;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isNull() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isType() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isArray() const
{
    return true;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isDynamicArray() const
{
    return true;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isMap() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isBoolean() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isNumber() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isIntegral() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isUnsigned() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isFloatingPoint() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::isString() const
{
    return false;
}

template <typename T, typename ET>
const T & BaseTypeImplVector<T, ET>::defaultValue() const
{
    static T value;

    return value;
}

template <typename T, typename ET>
std::string BaseTypeImplVector<T, ET>::toString(const T & var) const
{
    BaseType<ET> subType;

    std::string str = "(";

    for (size_t i=0; i<var.size(); i++)
    {
        if (i > 0) str += ", ";
        ET value = getElement(var, i);
        str += subType.toString(value);
    }

    str += ")";

    return str;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::fromString(T & var, const std::string & value) const
{
    BaseType<ET> subType;

    var.clear();

    std::vector<std::string> elementStrings = cppassist::string::parseArray(value, 0);

    for (size_t i=0; i<elementStrings.size(); i++)
    {
        ET value;

        if (!subType.fromString(value, elementStrings[i])) {
            return false;
        }

        push(var, value);
    }

    return true;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::toBool(const T &) const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::fromBool(T &, bool) const
{
    return false;
}

template <typename T, typename ET>
long long BaseTypeImplVector<T, ET>::toLongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::fromLongLong(T &, long long) const
{
    return false;
}

template <typename T, typename ET>
unsigned long long BaseTypeImplVector<T, ET>::toULongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::fromULongLong(T &, unsigned long long) const
{
    return false;
}

template <typename T, typename ET>
double BaseTypeImplVector<T, ET>::toDouble(const T &) const
{
    return 0.0;
}

template <typename T, typename ET>
bool BaseTypeImplVector<T, ET>::fromDouble(T &, double) const
{
    return false;
}

template <typename T, typename ET>
size_t BaseTypeImplVector<T, ET>::numElements(const T & var) const
{
    return var.size();
}

template <typename T, typename ET>
ET BaseTypeImplVector<T, ET>::getElement(const T & var, size_t i) const
{
    return var[i];
}

template <typename T, typename ET>
void BaseTypeImplVector<T, ET>::setElement(T & var, size_t i, ET value) const
{
    var[i] = value;
}

template <typename T, typename ET>
void BaseTypeImplVector<T, ET>::push(T & var, ET value) const
{
    var.push_back(value);
}

template <typename T, typename ET>
std::vector<std::string> BaseTypeImplVector<T, ET>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T, typename ET>
ET BaseTypeImplVector<T, ET>::getElement(const T &, const std::string &) const
{
    BaseType<ET> subType;
    return subType.defaultValue();
}

template <typename T, typename ET>
void BaseTypeImplVector<T, ET>::setElement(T &, const std::string &, ET) const
{
}


} // namespace cppexpose
