
#pragma once


#include <cppassist/string/conversion.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedSignedIntegral<Type>::TypedSignedIntegral(Args&&... args)
: AbstractTypedNumber<Type>(Type(0), std::forward<Args>(args)...)
{
}

template <typename Type>
TypedSignedIntegral<Type>::~TypedSignedIntegral()
{
}

template <typename Type>
std::string TypedSignedIntegral<Type>::typeName() const
{
    return "int" + cppassist::string::toString<unsigned int>(sizeof(Type) * 8);
}

template <typename Type>
bool TypedSignedIntegral<Type>::isIntegral() const
{
    return true;
}

template <typename Type>
bool TypedSignedIntegral<Type>::isSignedIntegral() const
{
    return true;
}

template <typename Type>
bool TypedSignedIntegral<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedSignedIntegral<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvertToLongLong()  ||
            value.canConvertToULongLong() ||
            value.canConvertToDouble()    ||
            value.canConvertToBool()      ||
            value.canConvertToString());
}

template <typename Type>
void TypedSignedIntegral<Type>::fromVar(const AbstractVar & value)
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
