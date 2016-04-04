
#pragma once


#include <cppexpose/typed/TypedUnsignedIntegral.h>

#include <sstream>


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
    std::stringstream s;
    s << "uint";
    s << sizeof(T) * 8;
    return s.str();
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
