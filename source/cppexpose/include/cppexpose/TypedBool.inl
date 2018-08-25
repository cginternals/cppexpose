
#pragma once


#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedBool<Type>::TypedBool(Args&&... args)
: ValueStorage<Type>(Type(false), std::forward<Args>(args)...)
{
}

template <typename Type>
TypedBool<Type>::~TypedBool()
{
}

template <typename Type>
VarType TypedBool<Type>::type() const
{
    return VarType::Bool;
}

template <typename Type>
std::string TypedBool<Type>::typeName() const
{
    return "bool";
}

template <typename Type>
bool TypedBool<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isBool() const
{
    return true;
}

template <typename Type>
bool TypedBool<Type>::isNumber() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isIntegral() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isString() const
{
    return true;
}

template <typename Type>
bool TypedBool<Type>::isExternal() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedBool<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedBool<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedBool<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedBool<Type>::canConvertToString() const
{
    // Well, yes
    return true;
}

template <typename Type>
std::string TypedBool<Type>::toString() const
{
    return this->value() ? "true" : "false";
}

template <typename Type>
bool TypedBool<Type>::canConvertToBool() const
{
    // Well, yes
    return true;
}

template <typename Type>
bool TypedBool<Type>::toBool() const
{
    return this->value();
}

template <typename Type>
bool TypedBool<Type>::canConvertToLongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type>
long long TypedBool<Type>::toLongLong() const
{
    return this->value() ? 1ll : 0ll;
}

template <typename Type>
bool TypedBool<Type>::canConvertToULongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type>
unsigned long long TypedBool<Type>::toULongLong() const
{
    return this->value() ? 1ull : 0ull;
}

template <typename Type>
bool TypedBool<Type>::canConvertToDouble() const
{
    // Generally, yes
    return true;
}

template <typename Type>
double TypedBool<Type>::toDouble() const
{
    return this->value() ? 1.0 : 0.0;
}

template <typename Type>
bool TypedBool<Type>::canConvertToObject() const
{
    // Converting a boolean to an object does not make sense
    return false;
}

template <typename Type>
Object TypedBool<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool TypedBool<Type>::canConvertToArray() const
{
    return false;
}

template <typename Type>
Array TypedBool<Type>::toArray() const
{
    return Array();
}

template <typename Type>
bool TypedBool<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvertToLongLong()  ||
            value.canConvertToULongLong() ||
            value.canConvertToDouble()    ||
            value.canConvertToBool()      ||
            value.canConvertToString());
}

template <typename Type>
void TypedBool<Type>::fromVar(const AbstractVar & value)
{
    if (value.canConvertToString()) {
        this->setValue(value.toString() == "true");
    } else if (value.canConvertToDouble()) {
        this->setValue(static_cast<bool>(value.toDouble()));
    } else if (value.canConvertToLongLong()) {
        this->setValue(static_cast<bool>(value.toLongLong()));
    } else if (value.canConvertToULongLong()) {
        this->setValue(static_cast<bool>(value.toULongLong()));
    } else if (value.canConvertToBool()) {
        this->setValue(value.toBool());
    } else if (value.canConvertToObject()) {
        // Cannot convert from object to boolean
    } else if (value.canConvertToArray()) {
        // Cannot convert from array to boolean
    }
}

template <typename Type>
const Object * TypedBool<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedBool<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
