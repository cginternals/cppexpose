
#pragma once


#include <string>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedArrayPointer<Type>::TypedArrayPointer(Args&&... args)
: ValueStorage<Type>(Type(nullptr), std::forward<Args>(args)...)
{
}

template <typename Type>
TypedArrayPointer<Type>::~TypedArrayPointer()
{
}

template <typename Type>
VarType TypedArrayPointer<Type>::type() const
{
    return VarType::Pointer;
}

template <typename Type>
bool TypedArrayPointer<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isNumber() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isIntegral() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isString() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isExternal() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isPointer() const
{
    return true;
}

template <typename Type>
bool TypedArrayPointer<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::isArrayPointer() const
{
    return true;
}

template <typename Type>
bool TypedArrayPointer<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedArrayPointer<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedArrayPointer<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedArrayPointer<Type>::canConvertToString() const
{
    return true;
}

template <typename Type>
std::string TypedArrayPointer<Type>::toString() const
{
    const Array * arr = this->value();

    if (arr) return arr->toString();
    else     return "[]";
}

template <typename Type>
bool TypedArrayPointer<Type>::canConvertToBool() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::toBool() const
{
    return false;
}

template <typename Type>
bool TypedArrayPointer<Type>::canConvertToLongLong() const
{
    return false;
}

template <typename Type>
long long TypedArrayPointer<Type>::toLongLong() const
{
    return 0ll;
}

template <typename Type>
bool TypedArrayPointer<Type>::canConvertToULongLong() const
{
    return true;
}

template <typename Type>
unsigned long long TypedArrayPointer<Type>::toULongLong() const
{
    return reinterpret_cast<unsigned long long>(reinterpret_cast<const void *>(this->value()));
}

template <typename Type>
bool TypedArrayPointer<Type>::canConvertToDouble() const
{
    return false;
}

template <typename Type>
double TypedArrayPointer<Type>::toDouble() const
{
    return 0.0;
}

template <typename Type>
bool TypedArrayPointer<Type>::canConvertToObject() const
{
    return false;
}

template <typename Type>
Object TypedArrayPointer<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool TypedArrayPointer<Type>::canConvertToArray() const
{
    return true;
}

template <typename Type>
Array TypedArrayPointer<Type>::toArray() const
{
    const Array * arr = this->value();

    if (arr) return *arr;
    else     return Array();
}

template <typename Type>
bool TypedArrayPointer<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvert<Type>() || value.canConvertToULongLong());
}

template <typename Type>
void TypedArrayPointer<Type>::fromVar(const AbstractVar & value)
{
    if (value.canConvert<Type>()) {
        this->setValue(value.convert<Type>());
    } else if (value.canConvertToULongLong()) {
        this->setValue(reinterpret_cast<Type>(reinterpret_cast<void *>(value.toULongLong())));
    }
}

template <typename Type>
const Object * TypedArrayPointer<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedArrayPointer<Type>::asArray() const
{
    return this->value();
}


} // namespace cppexpose
