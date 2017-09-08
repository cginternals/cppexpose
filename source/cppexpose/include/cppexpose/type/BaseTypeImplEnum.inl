
#pragma once


#include <typeinfo>
#include <sstream>

#include <cppassist/string/conversion.h>

#include <cppexpose/type/EnumValues.h>


namespace cppexpose
{


template <typename T>
BaseTypeImplEnum<T>::BaseTypeImplEnum()
{
    this->m_namedValues = EnumValues<T>::namedValues();
}

template <typename T>
BaseTypeImplEnum<T>::~BaseTypeImplEnum()
{
}

template <typename T>
std::string BaseTypeImplEnum<T>::typeName() const
{
    BaseType<typename std::underlying_type<T>::type> underlyingType;

    std::stringstream s;
    s << "enum<" << underlyingType.typeName() << ">";
    return s.str();
}

template <typename T>
bool BaseTypeImplEnum<T>::isNull() const
{
    return false;
}

template <typename T>
bool BaseTypeImplEnum<T>::isType() const
{
    return false;
}

template <typename T>
bool BaseTypeImplEnum<T>::isArray() const
{
    return false;
}

template <typename T>
bool BaseTypeImplEnum<T>::isDynamicArray() const
{
    return false;
}

template <typename T>
bool BaseTypeImplEnum<T>::isMap() const
{
    return false;
}

template <typename T>
bool BaseTypeImplEnum<T>::isBoolean() const
{
    return false;
}

template <typename T>
bool BaseTypeImplEnum<T>::isNumber() const
{
    return true;
}

template <typename T>
bool BaseTypeImplEnum<T>::isIntegral() const
{
    return true;
}

template <typename T>
bool BaseTypeImplEnum<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool BaseTypeImplEnum<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
bool BaseTypeImplEnum<T>::isString() const
{
    return false;
}

template <typename T>
const T & BaseTypeImplEnum<T>::defaultValue() const
{
    static T value = static_cast<T>(0);

    return value;
}

template <typename T>
std::string BaseTypeImplEnum<T>::toString(const T & var) const
{
    return cppassist::string::toString<UnderlyingType>(static_cast<UnderlyingType>(var));
}

template <typename T>
bool BaseTypeImplEnum<T>::fromString(T & var, const std::string & value) const
{
    var = static_cast<T>(cppassist::string::fromString<UnderlyingType>(value));
    return true;
}

template <typename T>
bool BaseTypeImplEnum<T>::toBool(const T & var) const
{
    return static_cast<bool>(var);
}

template <typename T>
bool BaseTypeImplEnum<T>::fromBool(T & var, bool value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
long long BaseTypeImplEnum<T>::toLongLong(const T & var) const
{
    return static_cast<long long>(var);
}

template <typename T>
bool BaseTypeImplEnum<T>::fromLongLong(T & var, long long value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
unsigned long long BaseTypeImplEnum<T>::toULongLong(const T & var) const
{
    return static_cast<unsigned long long>(var);
}

template <typename T>
bool BaseTypeImplEnum<T>::fromULongLong(T & var, unsigned long long value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
double BaseTypeImplEnum<T>::toDouble(const T & var) const
{
    return static_cast<double>(var);
}

template <typename T>
bool BaseTypeImplEnum<T>::fromDouble(T & var, double value) const
{
    // [TODO] Provide an UNUSED() macro in cppassist
    (void)(value);

    var = static_cast<T>(value);
    return true;
}

template <typename T>
size_t BaseTypeImplEnum<T>::numElements(const T &) const
{
    return 1;
}

template <typename T>
T BaseTypeImplEnum<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return this->defaultValue();
    }
}

template <typename T>
void BaseTypeImplEnum<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void BaseTypeImplEnum<T>::push(T &, T) const
{
}

template <typename T>
std::vector<std::string> BaseTypeImplEnum<T>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T>
T BaseTypeImplEnum<T>::getElement(const T &, const std::string &) const
{
    return this->defaultValue();
}

template <typename T>
void BaseTypeImplEnum<T>::setElement(T &, const std::string &, T) const
{
}


} // namespace cppexpose
