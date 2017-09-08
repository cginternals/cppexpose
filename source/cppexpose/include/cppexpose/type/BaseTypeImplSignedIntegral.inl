
#pragma once


#include <typeinfo>
#include <sstream>


namespace cppexpose
{


template <typename T>
BaseTypeImplSignedIntegral<T>::BaseTypeImplSignedIntegral()
{
}

template <typename T>
BaseTypeImplSignedIntegral<T>::~BaseTypeImplSignedIntegral()
{
}

template <typename T>
std::string BaseTypeImplSignedIntegral<T>::typeName() const
{
    std::stringstream s;
    s << "int";
    s << sizeof(T) * 8;
    return s.str();
}

template <typename T>
bool BaseTypeImplSignedIntegral<T>::isIntegral() const
{
    return true;
}

template <typename T>
bool BaseTypeImplSignedIntegral<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool BaseTypeImplSignedIntegral<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
const T & BaseTypeImplSignedIntegral<T>::defaultValue() const
{
    static T value = 0;

    return value;
}


} // namespace cppexpose
