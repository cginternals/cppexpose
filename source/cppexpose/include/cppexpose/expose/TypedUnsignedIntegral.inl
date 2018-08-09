
#pragma once


#include <cppassist/string/conversion.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedUnsignedIntegral<Type, Storage>::TypedUnsignedIntegral(Args&&... args)
: AbstractNumber<Type, Storage>(Type(0u), std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedUnsignedIntegral<Type, Storage>::~TypedUnsignedIntegral()
{
}

template <typename Type, typename Storage>
bool TypedUnsignedIntegral<Type, Storage>::isIntegral() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedUnsignedIntegral<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedUnsignedIntegral<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedUnsignedIntegral<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvertToLongLong()  ||
            value.canConvertToULongLong() ||
            value.canConvertToDouble()    ||
            value.canConvertToBool()      ||
            value.canConvertToString());
}

template <typename Type, typename Storage>
void TypedUnsignedIntegral<Type, Storage>::fromVar(const AbstractVar & value)
{
    if (value.canConvertToULongLong()) {
        this->setValue(static_cast<Type>(value.toULongLong()));
    } else if (value.canConvertToLongLong()) {
        this->setValue(static_cast<Type>(value.toLongLong()));
    } else if (value.canConvertToDouble()) {
        this->setValue(static_cast<Type>(value.toDouble()));
    } else if (value.canConvertToBool()) {
        this->setValue(static_cast<Type>(value.toBool()));
    } else if (value.canConvertToString()) {
        this->setValue(cppassist::string::fromString<Type>(value.toString()));
    } else if (value.canConvertToObject()) {
        // Cannot convert from object to number
    } else if (value.canConvertToArray()) {
        // Cannot convert from array to number
    }
}


} // namespace cppexpose
