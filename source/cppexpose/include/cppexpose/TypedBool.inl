
#pragma once


#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedBool<Type, Storage>::TypedBool(Args&&... args)
: Storage(Type(false), std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedBool<Type, Storage>::~TypedBool()
{
}

template <typename Type, typename Storage>
VarType TypedBool<Type, Storage>::type() const
{
    return VarType::Bool;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isBool() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isNumber() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isEnum() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isString() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isExternal() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isArray() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::isFunction() const
{
    return false;
}

template <typename Type, typename Storage>
Variant TypedBool<Type, Storage>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
Variant TypedBool<Type, Storage>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::canConvertToString() const
{
    // Well, yes
    return true;
}

template <typename Type, typename Storage>
std::string TypedBool<Type, Storage>::toString() const
{
    return this->getValue() ? "true" : "false";
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::canConvertToBool() const
{
    // Well, yes
    return true;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::toBool() const
{
    return this->getValue();
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::canConvertToLongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
long long TypedBool<Type, Storage>::toLongLong() const
{
    return this->getValue() ? 1ll : 0ll;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::canConvertToULongLong() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
unsigned long long TypedBool<Type, Storage>::toULongLong() const
{
    return this->getValue() ? 1ull : 0ull;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::canConvertToDouble() const
{
    // Generally, yes
    return true;
}

template <typename Type, typename Storage>
double TypedBool<Type, Storage>::toDouble() const
{
    return this->getValue() ? 1.0 : 0.0;
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::canConvertToObject() const
{
    // Converting a boolean to an object does not make sense
    return false;
}

template <typename Type, typename Storage>
Object TypedBool<Type, Storage>::toObject() const
{
    return Object();
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::canConvertToArray() const
{
    return false;
}

template <typename Type, typename Storage>
Array TypedBool<Type, Storage>::toArray() const
{
    return Array();
}

template <typename Type, typename Storage>
bool TypedBool<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvertToLongLong()  ||
            value.canConvertToULongLong() ||
            value.canConvertToDouble()    ||
            value.canConvertToBool()      ||
            value.canConvertToString());
}

template <typename Type, typename Storage>
void TypedBool<Type, Storage>::fromVar(const AbstractVar & value)
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

template <typename Type, typename Storage>
const Object * TypedBool<Type, Storage>::asObject() const
{
    return nullptr;
}

template <typename Type, typename Storage>
const Array * TypedBool<Type, Storage>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
