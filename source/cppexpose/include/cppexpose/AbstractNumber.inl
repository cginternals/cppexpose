
#pragma once


#include <limits>

#include <cppassist/string/conversion.h>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
AbstractNumber<Type>::AbstractNumber(Type defaultValue, Args&&... args)
: ValueStorage<Type>(defaultValue, std::forward<Args>(args)...)
, m_minValue(std::numeric_limits<Type>::lowest())
, m_maxValue(std::numeric_limits<Type>::max())
{
}

template <typename Type>
template <typename... Args>
AbstractNumber<Type>::AbstractNumber(Type defaultValue, Type value, Args&&... args)
: ValueStorage<Type>(defaultValue, value, std::forward<Args>(args)...)
, m_minValue(std::numeric_limits<Type>::lowest())
, m_maxValue(std::numeric_limits<Type>::max())
{
}

template <typename Type>
template <typename... Args>
AbstractNumber<Type>::AbstractNumber(Type defaultValue, Type value, Type minValue, Type maxValue, Args&&... args)
: ValueStorage<Type>(defaultValue, value, std::forward<Args>(args)...)
, m_minValue(minValue)
, m_maxValue(maxValue)
{
}

template <typename Type>
AbstractNumber<Type>::~AbstractNumber()
{
}

template <typename Type>
std::unique_ptr<AbstractVar> AbstractNumber<Type>::clone() const
{
    return std::unique_ptr<AbstractVar>(new Var<Type>(this->value(), this->m_minValue, this->m_maxValue));
}

template <typename Type>
VarType AbstractNumber<Type>::type() const
{
    return VarType::Number;
}

template <typename Type>
bool AbstractNumber<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isNumber() const
{
    return true;
}

template <typename Type>
bool AbstractNumber<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isString() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isExternal() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool AbstractNumber<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant AbstractNumber<Type>::minimumValue() const
{
    return Variant::fromValue<Type>(m_minValue);
}

template <typename Type>
Variant AbstractNumber<Type>::maximumValue() const
{
    return Variant::fromValue<Type>(m_maxValue);
}

template <typename Type>
bool AbstractNumber<Type>::canConvertToString() const
{
    // Yes, numbers can be converted to strings
    return true;
}

template <typename Type>
std::string AbstractNumber<Type>::toString() const
{
    // Convert number to string
    return cppassist::string::toString<Type>(this->value());
}

template <typename Type>
bool AbstractNumber<Type>::canConvertToBool() const
{
    // Generally, yes
    return true;
}

template <typename Type>
bool AbstractNumber<Type>::toBool() const
{
    return static_cast<bool>(this->value());
}

template <typename Type>
bool AbstractNumber<Type>::canConvertToLongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type>
long long AbstractNumber<Type>::toLongLong() const
{
    return static_cast<long long>(this->value());
}

template <typename Type>
bool AbstractNumber<Type>::canConvertToULongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type>
unsigned long long AbstractNumber<Type>::toULongLong() const
{
    return static_cast<unsigned long long>(this->value());
}

template <typename Type>
bool AbstractNumber<Type>::canConvertToDouble() const
{
    // Generally, yes
    return true;
}

template <typename Type>
double AbstractNumber<Type>::toDouble() const
{
    return static_cast<double>(this->value());
}

template <typename Type>
bool AbstractNumber<Type>::canConvertToObject() const
{
    // Converting a number to an object does not make sense
    return false;
}

template <typename Type>
Object AbstractNumber<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool AbstractNumber<Type>::canConvertToArray() const
{
    // Converting a number to an array does not make sense
    return false;
}

template <typename Type>
Array AbstractNumber<Type>::toArray() const
{
    return Array();
}

template <typename Type>
const Object * AbstractNumber<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * AbstractNumber<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
