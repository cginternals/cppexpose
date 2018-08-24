
#pragma once


#include <string>
#include <sstream>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedArrayPointer<Type, Storage>::TypedArrayPointer(Args&&... args)
: Storage(Type(nullptr), std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedArrayPointer<Type, Storage>::~TypedArrayPointer()
{
}

template <typename Type, typename Storage>
VarType TypedArrayPointer<Type, Storage>::type() const
{
    return VarType::Pointer;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isNumber() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isEnum() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isString() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isExternal() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isPointer() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isObjectPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isArray() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isArrayPointer() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::isFunction() const
{
    return false;
}

template <typename Type, typename Storage>
Variant TypedArrayPointer<Type, Storage>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
Variant TypedArrayPointer<Type, Storage>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::canConvertToString() const
{
    return true;
}

template <typename Type, typename Storage>
std::string TypedArrayPointer<Type, Storage>::toString() const
{
    const Array * arr = this->value();

    if (arr) return arr->toString();
    else     return "[]";
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::canConvertToBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::toBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::canConvertToLongLong() const
{
    return false;
}

template <typename Type, typename Storage>
long long TypedArrayPointer<Type, Storage>::toLongLong() const
{
    return 0ll;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::canConvertToULongLong() const
{
    return true;
}

template <typename Type, typename Storage>
unsigned long long TypedArrayPointer<Type, Storage>::toULongLong() const
{
    return reinterpret_cast<unsigned long long>(reinterpret_cast<const void *>(this->value()));
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::canConvertToDouble() const
{
    return false;
}

template <typename Type, typename Storage>
double TypedArrayPointer<Type, Storage>::toDouble() const
{
    return 0.0;
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::canConvertToObject() const
{
    return false;
}

template <typename Type, typename Storage>
Object TypedArrayPointer<Type, Storage>::toObject() const
{
    return Object();
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::canConvertToArray() const
{
    return true;
}

template <typename Type, typename Storage>
Array TypedArrayPointer<Type, Storage>::toArray() const
{
    const Array * arr = this->value();

    if (arr) return *arr;
    else     return Array();
}

template <typename Type, typename Storage>
bool TypedArrayPointer<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.hasType<Type>() || value.canConvert<Type>() || value.canConvertToULongLong());
}

template <typename Type, typename Storage>
void TypedArrayPointer<Type, Storage>::fromVar(const AbstractVar & value)
{
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        this->setValue(value.convert<Type>());
    } else if (value.canConvertToULongLong()) {
        this->setValue(reinterpret_cast<Type>(reinterpret_cast<void *>(value.toULongLong())));
    }
}

template <typename Type, typename Storage>
const Object * TypedArrayPointer<Type, Storage>::asObject() const
{
    return nullptr;
}

template <typename Type, typename Storage>
const Array * TypedArrayPointer<Type, Storage>::asArray() const
{
    return this->value();
}


} // namespace cppexpose
