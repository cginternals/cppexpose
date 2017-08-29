
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
TypeFloatingPoint<T>::TypeFloatingPoint()
{
}

template <typename T>
TypeFloatingPoint<T>::~TypeFloatingPoint()
{
}

template <typename T>
std::string TypeFloatingPoint<T>::typeName() const
{
         if (sizeof(T)  > sizeof(float)) return "double";
    else if (sizeof(T) == sizeof(float)) return "float";
    else                                 return "half";
}

template <typename T>
bool TypeFloatingPoint<T>::isIntegral() const
{
    return false;
}

template <typename T>
bool TypeFloatingPoint<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool TypeFloatingPoint<T>::isFloatingPoint() const
{
    return true;
}

template <typename T>
const T & TypeFloatingPoint<T>::defaultValue() const
{
    static T value = 0.0;

    return value;
}


} // namespace cppexpose
