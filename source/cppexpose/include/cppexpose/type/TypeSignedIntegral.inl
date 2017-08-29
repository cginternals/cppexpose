
#pragma once


#include <typeinfo>
#include <sstream>


namespace cppexpose
{


template <typename T>
TypeSignedIntegral<T>::TypeSignedIntegral()
{
}

template <typename T>
TypeSignedIntegral<T>::~TypeSignedIntegral()
{
}

template <typename T>
std::string TypeSignedIntegral<T>::typeName() const
{
    std::stringstream s;
    s << "int";
    s << sizeof(T) * 8;
    return s.str();
}

template <typename T>
bool TypeSignedIntegral<T>::isIntegral() const
{
    return true;
}

template <typename T>
bool TypeSignedIntegral<T>::isUnsigned() const
{
    return false;
}

template <typename T>
bool TypeSignedIntegral<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
const T & TypeSignedIntegral<T>::defaultValue() const
{
    static T value = 0;

    return value;
}


} // namespace cppexpose
