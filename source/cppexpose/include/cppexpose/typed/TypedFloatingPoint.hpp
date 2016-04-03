
#pragma once


#include <cppexpose/typed/TypedFloatingPoint.h>


namespace cppexpose
{


template <typename T>
TypedFloatingPoint<T>::TypedFloatingPoint()
{
}

template <typename T>
TypedFloatingPoint<T>::~TypedFloatingPoint()
{
}

template <typename T>
std::string TypedFloatingPoint<T>::typeName() const
{
    return "float";
}

template <typename T>
bool TypedFloatingPoint<T>::isFloatingPoint() const
{
    return true;
}


} // namespace cppexpose
