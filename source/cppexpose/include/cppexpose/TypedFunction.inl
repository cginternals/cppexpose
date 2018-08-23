
#pragma once


#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedFunction<Type, Storage>::TypedFunction(Args&&... args)
: Storage(std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedFunction<Type, Storage>::~TypedFunction()
{
}

template <typename Type, typename Storage>
VarType TypedFunction<Type, Storage>::type() const
{
    return VarType::Function;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isNumber() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isEnum() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isString() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isExternal() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isArray() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::isFunction() const
{
    return true;
}

template <typename Type, typename Storage>
Variant TypedFunction<Type, Storage>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
Variant TypedFunction<Type, Storage>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::canConvertToString() const
{
    return false;
}

template <typename Type, typename Storage>
std::string TypedFunction<Type, Storage>::toString() const
{
    return "";
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::canConvertToBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::toBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::canConvertToLongLong() const
{
    return false;
}

template <typename Type, typename Storage>
long long TypedFunction<Type, Storage>::toLongLong() const
{
    return 0ll;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::canConvertToULongLong() const
{
    return false;
}

template <typename Type, typename Storage>
unsigned long long TypedFunction<Type, Storage>::toULongLong() const
{
    return 0ull;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::canConvertToDouble() const
{
    return false;
}

template <typename Type, typename Storage>
double TypedFunction<Type, Storage>::toDouble() const
{
    return 0.0;
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::canConvertToObject() const
{
    return false;
}

template <typename Type, typename Storage>
Object TypedFunction<Type, Storage>::toObject() const
{
    return Object();
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::canConvertToArray() const
{
    return false;
}

template <typename Type, typename Storage>
Array TypedFunction<Type, Storage>::toArray() const
{
    return Array();
}

template <typename Type, typename Storage>
bool TypedFunction<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return value.isFunction();
}

template <typename Type, typename Storage>
void TypedFunction<Type, Storage>::fromVar(const AbstractVar & value)
{
    if (value.isFunction()) {
        this->setValue(value.convert<Type>());
    }
}

template <typename Type, typename Storage>
const Object * TypedFunction<Type, Storage>::asObject() const
{
    return nullptr;
}

template <typename Type, typename Storage>
const Array * TypedFunction<Type, Storage>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
