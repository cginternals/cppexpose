
#pragma once


#include <typeinfo>
#include <sstream>

#include <cppassist/string/manipulation.h>


namespace cppexpose
{


template <typename T>
class Type;


template <typename T, typename ET, size_t SIZE>
TypeArray<T, ET, SIZE>::TypeArray()
{
}

template <typename T, typename ET, size_t SIZE>
TypeArray<T, ET, SIZE>::~TypeArray()
{
}

template <typename T, typename ET, size_t SIZE>
const std::type_info & TypeArray<T, ET, SIZE>::typeInfo() const
{
    return typeid(T);
}

template <typename T, typename ET, size_t SIZE>
std::string TypeArray<T, ET, SIZE>::typeName() const
{
    Type<ET> subType;

    std::stringstream s;
    s << "array<" << subType.typeName() << ", " << SIZE << ">";
    return s.str();
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::isArray() const
{
    return true;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::isDynamicArray() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::isBoolean() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::isNumber() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::isIntegral() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::isUnsigned() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::isFloatingPoint() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::isString() const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
const T & TypeArray<T, ET, SIZE>::defaultValue() const
{
    static T value;

    return value;
}

template <typename T, typename ET, size_t SIZE>
std::string TypeArray<T, ET, SIZE>::toString(const T & var) const
{
    Type<ET> subType;

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
bool TypeArray<T, ET, SIZE>::fromString(T & var, const std::string & value) const
{
    Type<ET> subType;

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
bool TypeArray<T, ET, SIZE>::toBool(const T &) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::fromBool(T &, bool) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
long long TypeArray<T, ET, SIZE>::toLongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::fromLongLong(T &, long long) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
unsigned long long TypeArray<T, ET, SIZE>::toULongLong(const T &) const
{
    return 0;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::fromULongLong(T &, unsigned long long) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
double TypeArray<T, ET, SIZE>::toDouble(const T &) const
{
    return 0.0;
}

template <typename T, typename ET, size_t SIZE>
bool TypeArray<T, ET, SIZE>::fromDouble(T &, double) const
{
    return false;
}

template <typename T, typename ET, size_t SIZE>
size_t TypeArray<T, ET, SIZE>::numElements(const T &) const
{
    return SIZE;
}

template <typename T, typename ET, size_t SIZE>
ET TypeArray<T, ET, SIZE>::getElement(const T & var, size_t i) const
{
    return var[i];
}

template <typename T, typename ET, size_t SIZE>
void TypeArray<T, ET, SIZE>::setElement(T & var, size_t i, ET value) const
{
    var[i] = value;
}

template <typename T, typename ET, size_t SIZE>
void TypeArray<T, ET, SIZE>::push(T &, ET) const
{
    // Not supported for static arrays
}

template <typename T, typename ET, size_t SIZE>
std::vector<std::string> TypeArray<T, ET, SIZE>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T, typename ET, size_t SIZE>
ET TypeArray<T, ET, SIZE>::getElement(const T &, const std::string &) const
{
    Type<ET> subType;
    return subType.defaultValue();
}

template <typename T, typename ET, size_t SIZE>
void TypeArray<T, ET, SIZE>::setElement(T &, const std::string &, ET) const
{
}


} // namespace cppexpose
