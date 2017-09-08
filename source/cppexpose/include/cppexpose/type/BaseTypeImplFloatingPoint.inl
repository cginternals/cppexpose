
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
BaseTypeImplFloatingPoint<T>::BaseTypeImplFloatingPoint()
{
}

template <typename T>
BaseTypeImplFloatingPoint<T>::~BaseTypeImplFloatingPoint()
{
}

template <typename T>
std::string BaseTypeImplFloatingPoint<T>::typeName() const
{
         if (sizeof(T)  > sizeof(float)) return "double";
    else if (sizeof(T) == sizeof(float)) return "float";
    else                                 return "half";
}

template <typename T>
bool BaseTypeImplFloatingPoint<T>::isIntegral() const
{
    return false;
}

template <typename T>
bool BaseTypeImplFloatingPoint<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool BaseTypeImplFloatingPoint<T>::isFloatingPoint() const
{
    return true;
}

template <typename T>
const T & BaseTypeImplFloatingPoint<T>::defaultValue() const
{
    static T value = 0.0;

    return value;
}


} // namespace cppexpose
