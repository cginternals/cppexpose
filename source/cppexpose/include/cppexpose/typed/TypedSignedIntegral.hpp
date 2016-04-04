
#pragma once


#include <cppexpose/typed/TypedSignedIntegral.h>

#include <sstream>


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
    std::stringstream s;
    s << "int";
    s << sizeof(T) * 8;
    return s.str();
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
