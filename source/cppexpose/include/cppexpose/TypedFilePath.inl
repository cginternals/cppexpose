
#pragma once


#include <cppassist/string/conversion.h>

#include <cppexpose/AbstractTyped.h>
#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedFilePath<Type>::TypedFilePath(Args&&... args)
: ValueStorage<Type>(Type(""), std::forward<Args>(args)...)
{
}

template <typename Type>
TypedFilePath<Type>::~TypedFilePath()
{
}

template <typename Type>
std::vector<std::string> TypedFilePath<Type>::choices() const
{
    return m_choices;
}

template <typename Type>
void TypedFilePath<Type>::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
}

template <typename Type>
VarType TypedFilePath<Type>::type() const
{
    return VarType::String;
}

template <typename Type>
std::string TypedFilePath<Type>::typeName() const
{
    return "filename";
}

template <typename Type>
bool TypedFilePath<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isNumber() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isIntegral() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isString() const
{
    return true;
}

template <typename Type>
bool TypedFilePath<Type>::isExternal() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedFilePath<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedFilePath<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedFilePath<Type>::canConvertToString() const
{
    // Well, yes
    return true;
}

template <typename Type>
std::string TypedFilePath<Type>::toString() const
{
    return this->value().path();
}

template <typename Type>
bool TypedFilePath<Type>::canConvertToBool() const
{
    // No
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::toBool() const
{
    return false;
}

template <typename Type>
bool TypedFilePath<Type>::canConvertToLongLong() const
{
    // No
    return false;
}

template <typename Type>
long long TypedFilePath<Type>::toLongLong() const
{
    return 0ll;
}

template <typename Type>
bool TypedFilePath<Type>::canConvertToULongLong() const
{
    // No
    return false;
}

template <typename Type>
unsigned long long TypedFilePath<Type>::toULongLong() const
{
    return 0ull;
}

template <typename Type>
bool TypedFilePath<Type>::canConvertToDouble() const
{
    // No
    return false;
}

template <typename Type>
double TypedFilePath<Type>::toDouble() const
{
    return 0.0;
}

template <typename Type>
bool TypedFilePath<Type>::canConvertToObject() const
{
    // Converting a string to an object does not make sense
    return false;
}

template <typename Type>
Object TypedFilePath<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool TypedFilePath<Type>::canConvertToArray() const
{
    return false;
}

template <typename Type>
Array TypedFilePath<Type>::toArray() const
{
    return Array();
}

template <typename Type>
bool TypedFilePath<Type>::canConvertFromVar(const AbstractVar & value)
{
    return value.canConvertToString();
}

template <typename Type>
void TypedFilePath<Type>::fromVar(const AbstractVar & value)
{
    if (value.canConvertToString()) {
        this->setValue(value.toString());
    }
}

template <typename Type>
const Object * TypedFilePath<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedFilePath<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
