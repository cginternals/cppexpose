
#pragma once


#include <string>
#include <sstream>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedPointer<Type>::TypedPointer(Args&&... args)
: ValueStorage<Type>(Type(nullptr), std::forward<Args>(args)...)
{
}

template <typename Type>
TypedPointer<Type>::~TypedPointer()
{
}

template <typename Type>
VarType TypedPointer<Type>::type() const
{
    return VarType::Pointer;
}

template <typename Type>
bool TypedPointer<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isNumber() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isIntegral() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isString() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isExternal() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isPointer() const
{
    return true;
}

template <typename Type>
bool TypedPointer<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedPointer<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedPointer<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedPointer<Type>::canConvertToString() const
{
    return true;
}

template <typename Type>
std::string TypedPointer<Type>::toString() const
{
    // Get address
    const void * address = static_cast<const void*>(this->value());

    // Convert to string
    std::stringstream ss;
    ss << std::hex << address;

    // Return string representation
    std::string hex = ss.str();
    if (hex == "0") hex = "0x0";
    return hex;
}

template <typename Type>
bool TypedPointer<Type>::canConvertToBool() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::toBool() const
{
    return false;
}

template <typename Type>
bool TypedPointer<Type>::canConvertToLongLong() const
{
    return false;
}

template <typename Type>
long long TypedPointer<Type>::toLongLong() const
{
    return 0ll;
}

template <typename Type>
bool TypedPointer<Type>::canConvertToULongLong() const
{
    return true;
}

template <typename Type>
unsigned long long TypedPointer<Type>::toULongLong() const
{
    return reinterpret_cast<unsigned long long>(reinterpret_cast<const void *>(this->value()));
}

template <typename Type>
bool TypedPointer<Type>::canConvertToDouble() const
{
    return false;
}

template <typename Type>
double TypedPointer<Type>::toDouble() const
{
    return 0.0;
}

template <typename Type>
bool TypedPointer<Type>::canConvertToObject() const
{
    return false;
}

template <typename Type>
Object TypedPointer<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool TypedPointer<Type>::canConvertToArray() const
{
    return false;
}

template <typename Type>
Array TypedPointer<Type>::toArray() const
{
    return Array();
}

template <typename Type>
bool TypedPointer<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.hasType<Type>() || value.canConvert<Type>() || value.canConvertToULongLong());
}

template <typename Type>
void TypedPointer<Type>::fromVar(const AbstractVar & value)
{
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        this->setValue(value.convert<Type>());
    } else if (value.canConvertToULongLong()) {
        this->setValue(reinterpret_cast<Type>(reinterpret_cast<void *>(value.toULongLong())));
    }
}

template <typename Type>
const Object * TypedPointer<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedPointer<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
