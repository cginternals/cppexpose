
#pragma once


#include <typeinfo>

#include <cppassist/string/manipulation.h>


namespace cppexpose
{


template <typename T>
class Type;


template <typename T, typename ET>
TypeMap<T, ET>::TypeMap()
{
}

template <typename T, typename ET>
TypeMap<T, ET>::~TypeMap()
{
}

template <typename T, typename ET>
const std::type_info & TypeMap<T, ET>::typeInfo() const
{
    return typeid(T);
}

template <typename T, typename ET>
std::string TypeMap<T, ET>::typeName() const
{
    Type<ET> subType;

    std::stringstream s;
    s << "map<string, " << subType.typeName() << ">";
    return s.str();
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isNull() const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isArray() const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isDynamicArray() const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isMap() const
{
    return true;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isBoolean() const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isNumber() const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isIntegral() const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isUnsigned() const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isFloatingPoint() const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isString() const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::isType() const
{
    return false;
}

template <typename T, typename ET>
const T & TypeMap<T, ET>::defaultValue() const
{
    static T value;

    return value;
}

template <typename T, typename ET>
std::string TypeMap<T, ET>::toString(const T &) const
{
    // Not implemented
    return "";
}

template <typename T, typename ET>
bool TypeMap<T, ET>::fromString(T &, const std::string &) const
{
    // Not implemented
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::toBool(const T &) const
{
    return false;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::fromBool(T &, bool) const
{
    return false;
}

template <typename T, typename ET>
long long TypeMap<T, ET>::toLongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::fromLongLong(T &, long long) const
{
    return false;
}

template <typename T, typename ET>
unsigned long long TypeMap<T, ET>::toULongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::fromULongLong(T &, unsigned long long) const
{
    return false;
}

template <typename T, typename ET>
double TypeMap<T, ET>::toDouble(const T &) const
{
    return 0.0;
}

template <typename T, typename ET>
bool TypeMap<T, ET>::fromDouble(T &, double) const
{
    return false;
}

template <typename T, typename ET>
size_t TypeMap<T, ET>::numElements(const T &) const
{
    return 1;
}

template <typename T, typename ET>
ET TypeMap<T, ET>::getElement(const T &, size_t) const
{
    Type<ET> subType;
    return subType.defaultValue();
}

template <typename T, typename ET>
void TypeMap<T, ET>::setElement(T &, size_t, ET) const
{
}

template <typename T, typename ET>
void TypeMap<T, ET>::push(T &, ET) const
{
}

template <typename T, typename ET>
std::vector<std::string> TypeMap<T, ET>::keys(const T & var) const
{
    std::vector<std::string> keys;

    for (auto it : var) {
        keys.push_back(it.first);
    }

    return keys;
}

template <typename T, typename ET>
ET TypeMap<T, ET>::getElement(const T & var, const std::string & key) const
{
    auto it = var.find(key);

    if (it != var.end()) {
        return it->second;
    }

    else {
        Type<ET> subType;
        return subType.defaultValue();
    }
}

template <typename T, typename ET>
void TypeMap<T, ET>::setElement(T & var, const std::string & key, ET value) const
{
    var[key] = value;
}


} // namespace cppexpose
