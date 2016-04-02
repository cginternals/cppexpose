
#pragma once


#include <cppexpose/typed/TypedUnsignedIntegral.h>


namespace cppexpose
{


template <typename T>
TypedUnsignedIntegral<T>::TypedUnsignedIntegral()
{
}

template <typename T>
TypedUnsignedIntegral<T>::~TypedUnsignedIntegral()
{
}

template <typename T>
std::string TypedUnsignedIntegral<T>::typeName() const
{
    return "unsigned";
}

template <typename T>
bool TypedUnsignedIntegral<T>::isNumber() const
{
    return true;
}

template <typename T>
bool TypedUnsignedIntegral<T>::isIntegral() const
{
    return true;
}

template <typename T>
bool TypedUnsignedIntegral<T>::isUnsignedIntegral() const
{
    return true;
}


} // namespace cppexpose
