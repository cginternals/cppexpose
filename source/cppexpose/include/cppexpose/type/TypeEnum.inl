
#pragma once


#include <typeinfo>
#include <sstream>

#include <cppassist/string/conversion.h>

#include <cppexpose/type/EnumValues.h>


namespace cppexpose
{


template <typename T>
TypeEnum<T>::TypeEnum()
{
    this->m_namedValues = EnumValues<T>::namedValues();
}

template <typename T>
TypeEnum<T>::~TypeEnum()
{
}

template <typename T>
const std::type_info & TypeEnum<T>::typeInfo() const
{
    return typeid(T);
}

template <typename T>
std::string TypeEnum<T>::typeName() const
{
    Type<typename std::underlying_type<T>::type> underlyingType;

    std::stringstream s;
    s << "enum<" << underlyingType.typeName() << ">";
    return s.str();
}

template <typename T>
bool TypeEnum<T>::isArray() const
{
    return false;
}

template <typename T>
bool TypeEnum<T>::isDynamicArray() const
{
    return false;
}

template <typename T>
bool TypeEnum<T>::isMap() const
{
    return false;
}

template <typename T>
bool TypeEnum<T>::isBoolean() const
{
    return false;
}

template <typename T>
bool TypeEnum<T>::isNumber() const
{
    return true;
}

template <typename T>
bool TypeEnum<T>::isIntegral() const
{
    return true;
}

template <typename T>
bool TypeEnum<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool TypeEnum<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
bool TypeEnum<T>::isString() const
{
    return false;
}

template <typename T>
const T & TypeEnum<T>::defaultValue() const
{
    static T value = static_cast<T>(0);

    return value;
}

template <typename T>
std::string TypeEnum<T>::toString(const T & var) const
{
    return cppassist::string::toString<UnderlyingType>(static_cast<UnderlyingType>(var));
}

template <typename T>
bool TypeEnum<T>::fromString(T & var, const std::string & value) const
{
    var = static_cast<T>(cppassist::string::fromString<UnderlyingType>(value));
    return true;
}

template <typename T>
bool TypeEnum<T>::toBool(const T & var) const
{
    return static_cast<bool>(var);
}

template <typename T>
bool TypeEnum<T>::fromBool(T & var, bool value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
long long TypeEnum<T>::toLongLong(const T & var) const
{
    return static_cast<long long>(var);
}

template <typename T>
bool TypeEnum<T>::fromLongLong(T & var, long long value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
unsigned long long TypeEnum<T>::toULongLong(const T & var) const
{
    return static_cast<unsigned long long>(var);
}

template <typename T>
bool TypeEnum<T>::fromULongLong(T & var, unsigned long long value) const
{
    var = static_cast<T>(value);
    return true;
}

template <typename T>
double TypeEnum<T>::toDouble(const T & var) const
{
    return static_cast<double>(var);
}

template <typename T>
bool TypeEnum<T>::fromDouble(T & var, double value) const
{
    // [TODO] Provide an UNUSED() macro in cppassist
    (void)(value);

    var = static_cast<T>(value);
    return true;
}

template <typename T>
size_t TypeEnum<T>::numElements(const T &) const
{
    return 1;
}

template <typename T>
T TypeEnum<T>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return this->defaultValue();
    }
}

template <typename T>
void TypeEnum<T>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T>
void TypeEnum<T>::push(T &, T) const
{
}

template <typename T>
std::vector<std::string> TypeEnum<T>::keys(const T &) const
{
    return std::vector<std::string>();
}

template <typename T>
T TypeEnum<T>::getElement(const T &, const std::string &) const
{
    return this->defaultValue();
}

template <typename T>
void TypeEnum<T>::setElement(T &, const std::string &, T) const
{
}


} // namespace cppexpose
