
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
AbstractTypedNumber<Type>::AbstractTypedNumber(Type defaultValue, Args&&... args)
: ValueStorage<Type>(defaultValue, std::forward<Args>(args)...)
, m_minValue(std::numeric_limits<Type>::lowest())
, m_maxValue(std::numeric_limits<Type>::max())
{
}

template <typename Type>
template <typename... Args>
AbstractTypedNumber<Type>::AbstractTypedNumber(Type defaultValue, Type value, Args&&... args)
: ValueStorage<Type>(defaultValue, value, std::forward<Args>(args)...)
, m_minValue(std::numeric_limits<Type>::lowest())
, m_maxValue(std::numeric_limits<Type>::max())
{
}

template <typename Type>
template <typename... Args>
AbstractTypedNumber<Type>::AbstractTypedNumber(Type defaultValue, Type value, Type minValue, Type maxValue, Args&&... args)
: ValueStorage<Type>(defaultValue, value, std::forward<Args>(args)...)
, m_minValue(minValue)
, m_maxValue(maxValue)
{
}

template <typename Type>
AbstractTypedNumber<Type>::~AbstractTypedNumber()
{
}

template <typename Type>
std::unique_ptr<AbstractVar> AbstractTypedNumber<Type>::clone() const
{
    return std::unique_ptr<AbstractVar>(new Var<Type>(this->value(), this->m_minValue, this->m_maxValue));
}

template <typename Type>
VarType AbstractTypedNumber<Type>::type() const
{
    return VarType::Number;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isNumber() const
{
    return true;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isString() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isExternal() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool AbstractTypedNumber<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant AbstractTypedNumber<Type>::minimumValue() const
{
    return Variant::fromValue<Type>(m_minValue);
}

template <typename Type>
Variant AbstractTypedNumber<Type>::maximumValue() const
{
    return Variant::fromValue<Type>(m_maxValue);
}

template <typename Type>
bool AbstractTypedNumber<Type>::canConvertToString() const
{
    // Yes, numbers can be converted to strings
    return true;
}

template <typename Type>
std::string AbstractTypedNumber<Type>::toString() const
{
    // Convert number to string
    return cppassist::string::toString<Type>(this->value());
}

template <typename Type>
bool AbstractTypedNumber<Type>::canConvertToBool() const
{
    // Generally, yes
    return true;
}

template <typename Type>
bool AbstractTypedNumber<Type>::toBool() const
{
    return static_cast<bool>(this->value());
}

template <typename Type>
bool AbstractTypedNumber<Type>::canConvertToLongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type>
long long AbstractTypedNumber<Type>::toLongLong() const
{
    return static_cast<long long>(this->value());
}

template <typename Type>
bool AbstractTypedNumber<Type>::canConvertToULongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type>
unsigned long long AbstractTypedNumber<Type>::toULongLong() const
{
    return static_cast<unsigned long long>(this->value());
}

template <typename Type>
bool AbstractTypedNumber<Type>::canConvertToDouble() const
{
    // Generally, yes
    return true;
}

template <typename Type>
double AbstractTypedNumber<Type>::toDouble() const
{
    return static_cast<double>(this->value());
}

template <typename Type>
bool AbstractTypedNumber<Type>::canConvertToObject() const
{
    // Converting a number to an object does not make sense
    return false;
}

template <typename Type>
Object AbstractTypedNumber<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool AbstractTypedNumber<Type>::canConvertToArray() const
{
    // Converting a number to an array does not make sense
    return false;
}

template <typename Type>
Array AbstractTypedNumber<Type>::toArray() const
{
    return Array();
}

template <typename Type>
const Object * AbstractTypedNumber<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * AbstractTypedNumber<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
