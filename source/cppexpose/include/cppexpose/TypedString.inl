
#pragma once


#include <cppassist/string/conversion.h>

#include <cppexpose/AbstractTyped.h>
#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedString<Type>::TypedString(Args&&... args)
: ValueStorage<Type>(Type(""), std::forward<Args>(args)...)
{
}

template <typename Type>
TypedString<Type>::~TypedString()
{
}

template <typename Type>
std::vector<std::string> TypedString<Type>::choices() const
{
    return m_choices;
}

template <typename Type>
void TypedString<Type>::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
}

template <typename Type>
VarType TypedString<Type>::type() const
{
    return VarType::String;
}

template <typename Type>
std::string TypedString<Type>::typeName() const
{
    return "string";
}

template <typename Type>
bool TypedString<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isNumber() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isIntegral() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isString() const
{
    return true;
}

template <typename Type>
bool TypedString<Type>::isExternal() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedString<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedString<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedString<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedString<Type>::canConvertToString() const
{
    // Well, yes
    return true;
}

template <typename Type>
std::string TypedString<Type>::toString() const
{
    return this->value();
}

template <typename Type>
bool TypedString<Type>::canConvertToBool() const
{
    // Generally, yes
    return true;
}

template <typename Type>
bool TypedString<Type>::toBool() const
{
    return (this->value() == "true");
}

template <typename Type>
bool TypedString<Type>::canConvertToLongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type>
long long TypedString<Type>::toLongLong() const
{
    return cppassist::string::fromString<long long>(this->value());
}

template <typename Type>
bool TypedString<Type>::canConvertToULongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type>
unsigned long long TypedString<Type>::toULongLong() const
{
    return cppassist::string::fromString<unsigned long long>(this->value());
}

template <typename Type>
bool TypedString<Type>::canConvertToDouble() const
{
    // Generally, yes
    return true;
}

template <typename Type>
double TypedString<Type>::toDouble() const
{
    return cppassist::string::fromString<double>(this->value());
}

template <typename Type>
bool TypedString<Type>::canConvertToObject() const
{
    // Converting a string to an object does not make sense
    return false;
}

template <typename Type>
Object TypedString<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool TypedString<Type>::canConvertToArray() const
{
    return false;
}

template <typename Type>
Array TypedString<Type>::toArray() const
{
    return Array();
}

template <typename Type>
bool TypedString<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvertToLongLong()  ||
            value.canConvertToULongLong() ||
            value.canConvertToDouble()    ||
            value.canConvertToBool()      ||
            value.canConvertToString());
}

template <typename Type>
void TypedString<Type>::fromVar(const AbstractVar & value)
{
    if (value.canConvertToString()) {
        this->setValue(value.toString());
    } else if (value.canConvertToDouble()) {
        this->setValue(cppassist::string::toString<double>(value.toDouble()));
    } else if (value.canConvertToLongLong()) {
        this->setValue(cppassist::string::toString<double>(value.toLongLong()));
    } else if (value.canConvertToULongLong()) {
        this->setValue(cppassist::string::toString<double>(value.toULongLong()));
    } else if (value.canConvertToBool()) {
        this->setValue(value.toBool() ? "true" : "false");
    } else if (value.canConvertToObject()) {
        // Cannot convert from object to string
    } else if (value.canConvertToArray()) {
        // Cannot convert from array to string
    }
}

template <typename Type>
const Object * TypedString<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedString<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
