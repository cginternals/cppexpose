
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
TypedPointer<Type, Storage>::TypedPointer(Args&&... args)
: Storage(Type(nullptr), std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedPointer<Type, Storage>::~TypedPointer()
{
}

template <typename Type, typename Storage>
VarType TypedPointer<Type, Storage>::type() const
{
    return VarType::Pointer;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isNumber() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isEnum() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isString() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isExternal() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isPointer() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isArray() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::isFunction() const
{
    return false;
}

template <typename Type, typename Storage>
Variant TypedPointer<Type, Storage>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
Variant TypedPointer<Type, Storage>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::canConvertToString() const
{
    return true;
}

template <typename Type, typename Storage>
std::string TypedPointer<Type, Storage>::toString() const
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

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::canConvertToBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::toBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::canConvertToLongLong() const
{
    return false;
}

template <typename Type, typename Storage>
long long TypedPointer<Type, Storage>::toLongLong() const
{
    return 0ll;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::canConvertToULongLong() const
{
    return true;
}

template <typename Type, typename Storage>
unsigned long long TypedPointer<Type, Storage>::toULongLong() const
{
    return reinterpret_cast<unsigned long long>(reinterpret_cast<const void *>(this->value()));
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::canConvertToDouble() const
{
    return false;
}

template <typename Type, typename Storage>
double TypedPointer<Type, Storage>::toDouble() const
{
    return 0.0;
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::canConvertToObject() const
{
    return false;
}

template <typename Type, typename Storage>
Object TypedPointer<Type, Storage>::toObject() const
{
    return Object();
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::canConvertToArray() const
{
    return false;
}

template <typename Type, typename Storage>
Array TypedPointer<Type, Storage>::toArray() const
{
    return Array();
}

template <typename Type, typename Storage>
bool TypedPointer<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.hasType<Type>() || value.canConvert<Type>() || value.canConvertToULongLong());
}

template <typename Type, typename Storage>
void TypedPointer<Type, Storage>::fromVar(const AbstractVar & value)
{
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        this->setValue(value.value<Type>());
    } else if (value.canConvertToULongLong()) {
        this->setValue(reinterpret_cast<Type>(reinterpret_cast<void *>(value.toULongLong())));
    }
}

template <typename Type, typename Storage>
const Object * TypedPointer<Type, Storage>::asObject() const
{
    return nullptr;
}

template <typename Type, typename Storage>
const Array * TypedPointer<Type, Storage>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
