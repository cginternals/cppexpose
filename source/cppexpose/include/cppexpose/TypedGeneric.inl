
#pragma once


#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedGeneric<Type>::TypedGeneric(Args&&... args)
: ValueStorage<Type>(std::forward<Args>(args)...)
{
}

template <typename Type>
TypedGeneric<Type>::~TypedGeneric()
{
}

template <typename Type>
VarType TypedGeneric<Type>::type() const
{
    return VarType::External;
}

template <typename Type>
bool TypedGeneric<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isNumber() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isIntegral() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isString() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isExternal() const
{
    return true;
}

template <typename Type>
bool TypedGeneric<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedGeneric<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedGeneric<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedGeneric<Type>::canConvertToString() const
{
    return false;
}

template <typename Type>
std::string TypedGeneric<Type>::toString() const
{
    return "";
}

template <typename Type>
bool TypedGeneric<Type>::canConvertToBool() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::toBool() const
{
    return false;
}

template <typename Type>
bool TypedGeneric<Type>::canConvertToLongLong() const
{
    return false;
}

template <typename Type>
long long TypedGeneric<Type>::toLongLong() const
{
    return 0ll;
}

template <typename Type>
bool TypedGeneric<Type>::canConvertToULongLong() const
{
    return false;
}

template <typename Type>
unsigned long long TypedGeneric<Type>::toULongLong() const
{
    return 0ull;
}

template <typename Type>
bool TypedGeneric<Type>::canConvertToDouble() const
{
    return false;
}

template <typename Type>
double TypedGeneric<Type>::toDouble() const
{
    return 0.0;
}

template <typename Type>
bool TypedGeneric<Type>::canConvertToObject() const
{
    return false;
}

template <typename Type>
Object TypedGeneric<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool TypedGeneric<Type>::canConvertToArray() const
{
    return false;
}

template <typename Type>
Array TypedGeneric<Type>::toArray() const
{
    return Array();
}

template <typename Type>
bool TypedGeneric<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.hasType<Type>() || value.canConvert<Type>());
}

template <typename Type>
void TypedGeneric<Type>::fromVar(const AbstractVar & value)
{
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        this->setValue(value.convert<Type>());
    }
}

template <typename Type>
const Object * TypedGeneric<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedGeneric<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
