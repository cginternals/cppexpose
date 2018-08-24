
#pragma once


#include <cppassist/string/conversion.h>

#include <cppexpose/AbstractTyped.h>
#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedString<Type, Storage>::TypedString(Args&&... args)
: Storage(Type(""), std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedString<Type, Storage>::~TypedString()
{
}

template <typename Type, typename Storage>
std::vector<std::string> TypedString<Type, Storage>::choices() const
{
    return m_choices;
}

template <typename Type, typename Storage>
void TypedString<Type, Storage>::setChoices(const std::vector<std::string> & choices)
{
    m_choices = choices;
}

template <typename Type, typename Storage>
VarType TypedString<Type, Storage>::type() const
{
    return VarType::String;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isNumber() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isEnum() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isString() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isExternal() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isObjectPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isArray() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isArrayPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::isFunction() const
{
    return false;
}

template <typename Type, typename Storage>
Variant TypedString<Type, Storage>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
Variant TypedString<Type, Storage>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::canConvertToString() const
{
    // Well, yes
    return true;
}

template <typename Type, typename Storage>
std::string TypedString<Type, Storage>::toString() const
{
    return this->value();
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::canConvertToBool() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::toBool() const
{
    return (this->value() == "true");
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::canConvertToLongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
long long TypedString<Type, Storage>::toLongLong() const
{
    return cppassist::string::fromString<long long>(this->value());
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::canConvertToULongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
unsigned long long TypedString<Type, Storage>::toULongLong() const
{
    return cppassist::string::fromString<unsigned long long>(this->value());
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::canConvertToDouble() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
double TypedString<Type, Storage>::toDouble() const
{
    return cppassist::string::fromString<double>(this->value());
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::canConvertToObject() const
{
    // Converting a string to an object does not make sense
    return false;
}

template <typename Type, typename Storage>
Object TypedString<Type, Storage>::toObject() const
{
    return Object();
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::canConvertToArray() const
{
    return false;
}

template <typename Type, typename Storage>
Array TypedString<Type, Storage>::toArray() const
{
    return Array();
}

template <typename Type, typename Storage>
bool TypedString<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvertToLongLong()  ||
            value.canConvertToULongLong() ||
            value.canConvertToDouble()    ||
            value.canConvertToBool()      ||
            value.canConvertToString());
}

template <typename Type, typename Storage>
void TypedString<Type, Storage>::fromVar(const AbstractVar & value)
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

template <typename Type, typename Storage>
const Object * TypedString<Type, Storage>::asObject() const
{
    return nullptr;
}

template <typename Type, typename Storage>
const Array * TypedString<Type, Storage>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
