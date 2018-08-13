
#pragma once


#include <cppassist/string/conversion.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedSignedIntegral<Type, Storage>::TypedSignedIntegral(Args&&... args)
: AbstractNumber<Type, Storage>(Type(0), std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedSignedIntegral<Type, Storage>::~TypedSignedIntegral()
{
}

template <typename Type, typename Storage>
bool TypedSignedIntegral<Type, Storage>::isIntegral() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedSignedIntegral<Type, Storage>::isSignedIntegral() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedSignedIntegral<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedSignedIntegral<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvertToLongLong()  ||
            value.canConvertToULongLong() ||
            value.canConvertToDouble()    ||
            value.canConvertToBool()      ||
            value.canConvertToString());
}

template <typename Type, typename Storage>
void TypedSignedIntegral<Type, Storage>::fromVar(const AbstractVar & value)
{
    if (value.canConvertToLongLong()) {
        this->setValue(static_cast<Type>(value.toLongLong()));
    } else if (value.canConvertToULongLong()) {
        this->setValue(static_cast<Type>(value.toULongLong()));
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
