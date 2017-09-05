
#pragma once


#include <typeinfo>

#include <cppassist/string/manipulation.h>


namespace cppexpose
{


template <typename T>
class Type;


template <typename T, typename ET>
TypeVector<T, ET>::TypeVector()
{
}

template <typename T, typename ET>
TypeVector<T, ET>::~TypeVector()
{
}

template <typename T, typename ET>
const std::type_info & TypeVector<T, ET>::typeInfo() const
{
    return typeid(T);
}

template <typename T, typename ET>
std::string TypeVector<T, ET>::typeName() const
{
    Type<ET> subType;

    std::stringstream s;
    s << "vector<" << subType.typeName() << ">";
    return s.str();
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isNull() const
{
    return false;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isArray() const
{
    return true;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isDynamicArray() const
{
    return true;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isMap() const
{
    return false;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isBoolean() const
{
    return false;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isNumber() const
{
    return false;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isIntegral() const
{
    return false;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isUnsigned() const
{
    return false;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isFloatingPoint() const
{
    return false;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isString() const
{
    return false;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::isType() const
{
    return false;
}

template <typename T, typename ET>
const T & TypeVector<T, ET>::defaultValue() const
{
    static T value;

    return value;
}

template <typename T, typename ET>
std::string TypeVector<T, ET>::toString(const T & var) const
{
    Type<ET> subType;

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
bool TypeVector<T, ET>::fromString(T & var, const std::string & value) const
{
    Type<ET> subType;

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
bool TypeVector<T, ET>::toBool(const T &) const
{
    return false;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::fromBool(T &, bool) const
{
    return false;
}

template <typename T, typename ET>
long long TypeVector<T, ET>::toLongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::fromLongLong(T &, long long) const
{
    return false;
}

template <typename T, typename ET>
unsigned long long TypeVector<T, ET>::toULongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::fromULongLong(T &, unsigned long long) const
{
    return false;
}

template <typename T, typename ET>
double TypeVector<T, ET>::toDouble(const T &) const
{
    return 0.0;
}

template <typename T, typename ET>
bool TypeVector<T, ET>::fromDouble(T &, double) const
{
    return false;
}

template <typename T, typename ET>
size_t TypeVector<T, ET>::numElements(const T & var) const
{
    return var.size();
}

template <typename T, typename ET>
ET TypeVector<T, ET>::getElement(const T & var, size_t i) const
{
    return var[i];
}

template <typename T, typename ET>
void TypeVector<T, ET>::setElement(T & var, size_t i, ET value) const
{
    var[i] = value;
}

template <typename T, typename ET>
void TypeVector<T, ET>::push(T & var, ET value) const
{
    var.push_back(value);
}

template <typename T, typename ET>
std::vector<std::string> TypeVector<T, ET>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T, typename ET>
ET TypeVector<T, ET>::getElement(const T &, const std::string &) const
{
    Type<ET> subType;
    return subType.defaultValue();
}

template <typename T, typename ET>
void TypeVector<T, ET>::setElement(T &, const std::string &, ET) const
{
}


} // namespace cppexpose
