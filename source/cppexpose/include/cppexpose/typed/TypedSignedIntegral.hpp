
#pragma once


#include <cppexpose/typed/TypedSignedIntegral.h>


namespace cppexpose
{


template <typename T>
TypedSignedIntegral<T>::TypedSignedIntegral()
{
}

template <typename T>
TypedSignedIntegral<T>::~TypedSignedIntegral()
{
}

template <typename T>
std::string TypedSignedIntegral<T>::typeName() const
{
    return "int";
}

template <typename T>
bool TypedSignedIntegral<T>::isIntegral() const
{
    return true;
}

template <typename T>
bool TypedSignedIntegral<T>::isSignedIntegral() const
{
    return true;
}


} // namespace cppexpose
