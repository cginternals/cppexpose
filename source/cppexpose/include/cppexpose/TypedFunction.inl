
#pragma once


#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedFunction<Type>::TypedFunction(Args&&... args)
: ValueStorage<Type>(std::forward<Args>(args)...)
{
}

template <typename Type>
TypedFunction<Type>::~TypedFunction()
{
}

template <typename Type>
VarType TypedFunction<Type>::type() const
{
    return VarType::Function;
}

template <typename Type>
std::string TypedFunction<Type>::typeName() const
{
    return "function";
}

template <typename Type>
bool TypedFunction<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isNumber() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isIntegral() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isString() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isExternal() const
{
    return true;
}

template <typename Type>
bool TypedFunction<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::isFunction() const
{
    return true;
}

template <typename Type>
Variant TypedFunction<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedFunction<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedFunction<Type>::canConvertToString() const
{
    return false;
}

template <typename Type>
std::string TypedFunction<Type>::toString() const
{
    return "";
}

template <typename Type>
bool TypedFunction<Type>::canConvertToBool() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::toBool() const
{
    return false;
}

template <typename Type>
bool TypedFunction<Type>::canConvertToLongLong() const
{
    return false;
}

template <typename Type>
long long TypedFunction<Type>::toLongLong() const
{
    return 0ll;
}

template <typename Type>
bool TypedFunction<Type>::canConvertToULongLong() const
{
    return false;
}

template <typename Type>
unsigned long long TypedFunction<Type>::toULongLong() const
{
    return 0ull;
}

template <typename Type>
bool TypedFunction<Type>::canConvertToDouble() const
{
    return false;
}

template <typename Type>
double TypedFunction<Type>::toDouble() const
{
    return 0.0;
}

template <typename Type>
bool TypedFunction<Type>::canConvertToObject() const
{
    return false;
}

template <typename Type>
Object TypedFunction<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool TypedFunction<Type>::canConvertToArray() const
{
    return false;
}

template <typename Type>
Array TypedFunction<Type>::toArray() const
{
    return Array();
}

template <typename Type>
bool TypedFunction<Type>::canConvertFromVar(const AbstractVar & value)
{
    return value.isFunction();
}

template <typename Type>
void TypedFunction<Type>::fromVar(const AbstractVar & value)
{
    if (value.isFunction()) {
        this->setValue(value.convert<Type>());
    }
}

template <typename Type>
const Object * TypedFunction<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedFunction<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
