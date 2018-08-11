
#pragma once


#include <cppexpose/expose/Variant.h>
#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Array.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedGeneric<Type, Storage>::TypedGeneric(Args&&... args)
: Storage(std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedGeneric<Type, Storage>::~TypedGeneric()
{
}

template <typename Type, typename Storage>
VarType TypedGeneric<Type, Storage>::type() const
{
    return VarType::External;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isNumber() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isEnum() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isString() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isExternal() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isArray() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::isFunction() const
{
    return false;
}

template <typename Type, typename Storage>
Variant TypedGeneric<Type, Storage>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
Variant TypedGeneric<Type, Storage>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::canConvertToString() const
{
    return false;
}

template <typename Type, typename Storage>
std::string TypedGeneric<Type, Storage>::toString() const
{
    return "";
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::canConvertToBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::toBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::canConvertToLongLong() const
{
    return false;
}

template <typename Type, typename Storage>
long long TypedGeneric<Type, Storage>::toLongLong() const
{
    return 0ll;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::canConvertToULongLong() const
{
    return false;
}

template <typename Type, typename Storage>
unsigned long long TypedGeneric<Type, Storage>::toULongLong() const
{
    return 0ull;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::canConvertToDouble() const
{
    return false;
}

template <typename Type, typename Storage>
double TypedGeneric<Type, Storage>::toDouble() const
{
    return 0.0;
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::canConvertToObject() const
{
    return false;
}

template <typename Type, typename Storage>
Object TypedGeneric<Type, Storage>::toObject() const
{
    return Object();
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::canConvertToArray() const
{
    return false;
}

template <typename Type, typename Storage>
Array TypedGeneric<Type, Storage>::toArray() const
{
    return Array();
}

template <typename Type, typename Storage>
bool TypedGeneric<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.hasType<Type>() || value.canConvert<Type>());
}

template <typename Type, typename Storage>
void TypedGeneric<Type, Storage>::fromVar(const AbstractVar & value)
{
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        this->setValue(value.value<Type>());
    }
}

template <typename Type, typename Storage>
const Object * TypedGeneric<Type, Storage>::asObject() const
{
    return nullptr;
}

template <typename Type, typename Storage>
const Array * TypedGeneric<Type, Storage>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
