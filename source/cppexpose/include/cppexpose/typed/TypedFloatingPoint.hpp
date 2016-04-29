
#pragma once


#include <cppexpose/typed/TypedFloatingPoint.hh>


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
         if (sizeof(T)  > sizeof(float)) return "double";
    else if (sizeof(T) == sizeof(float)) return "float";
    else                                 return "half";
}

template <typename T>
bool TypedFloatingPoint<T>::isFloatingPoint() const
{
    return true;
}


} // namespace cppexpose
