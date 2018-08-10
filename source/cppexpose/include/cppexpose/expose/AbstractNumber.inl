
#pragma once


#include <limits>

#include <cppassist/string/conversion.h>

#include <cppexpose/expose/Variant.h>
#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Array.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
AbstractNumber<Type, Storage>::AbstractNumber(Type defaultValue, Args&&... args)
: Storage(defaultValue, std::forward<Args>(args)...)
, m_minValue(std::numeric_limits<Type>::lowest())
, m_maxValue(std::numeric_limits<Type>::max())
{
}

template <typename Type, typename Storage>
template <typename... Args>
AbstractNumber<Type, Storage>::AbstractNumber(Type defaultValue, Type value, Args&&... args)
: Storage(defaultValue, value, std::forward<Args>(args)...)
, m_minValue(std::numeric_limits<Type>::lowest())
, m_maxValue(std::numeric_limits<Type>::max())
{
}

template <typename Type, typename Storage>
template <typename... Args>
AbstractNumber<Type, Storage>::AbstractNumber(Type defaultValue, Type value, Type minValue, Type maxValue, Args&&... args)
: Storage(defaultValue, value, std::forward<Args>(args)...)
, m_minValue(minValue)
, m_maxValue(maxValue)
{
}

template <typename Type, typename Storage>
AbstractNumber<Type, Storage>::~AbstractNumber()
{
}

template <typename Type, typename Storage>
AbstractVar * AbstractNumber<Type, Storage>::clone() const
{
    return new Var<Type>(this->value(), this->m_minValue, this->m_maxValue);
}

template <typename Type, typename Storage>
VarType AbstractNumber<Type, Storage>::type() const
{
    return VarType::Number;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isNumber() const
{
    return true;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isEnum() const
{
    return false;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isString() const
{
    return false;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isExternal() const
{
    return false;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isArray() const
{
    return false;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::isFunction() const
{
    return false;
}

template <typename Type, typename Storage>
Variant AbstractNumber<Type, Storage>::minimumValue() const
{
    return Variant::fromValue<Type>(m_minValue);
}

template <typename Type, typename Storage>
Variant AbstractNumber<Type, Storage>::maximumValue() const
{
    return Variant::fromValue<Type>(m_maxValue);
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::canConvertToString() const
{
    // Yes, numbers can be converted to strings
    return true;
}

template <typename Type, typename Storage>
std::string AbstractNumber<Type, Storage>::toString() const
{
    // Convert number to string
    return cppassist::string::toString<Type>(this->value());
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::canConvertToBool() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::toBool() const
{
    return static_cast<bool>(this->value());
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::canConvertToLongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
long long AbstractNumber<Type, Storage>::toLongLong() const
{
    return static_cast<long long>(this->value());
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::canConvertToULongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
unsigned long long AbstractNumber<Type, Storage>::toULongLong() const
{
    return static_cast<unsigned long long>(this->value());
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::canConvertToDouble() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
double AbstractNumber<Type, Storage>::toDouble() const
{
    return static_cast<double>(this->value());
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::canConvertToObject() const
{
    // Converting a number to an object does not make sense
    return false;
}

template <typename Type, typename Storage>
Object AbstractNumber<Type, Storage>::toObject() const
{
    return Object();
}

template <typename Type, typename Storage>
bool AbstractNumber<Type, Storage>::canConvertToArray() const
{
    // Converting a number to an array does not make sense
    return false;
}

template <typename Type, typename Storage>
Array AbstractNumber<Type, Storage>::toArray() const
{
    return Array();
}


} // namespace cppexpose