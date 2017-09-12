
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
const std::string & BaseTypeImplFloatingPoint<T>::typeName() const
{
    static const auto name = sizeof(T) >= sizeof(long double) ? std::string("ldouble") :
                             sizeof(T) >= sizeof(double)      ? std::string("double") :
                             sizeof(T) >= sizeof(float)       ? std::string("float") :
                                                                std::string("half");

    return name;
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
