
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
TypeUnsignedIntegral<T>::TypeUnsignedIntegral()
{
}

template <typename T>
TypeUnsignedIntegral<T>::~TypeUnsignedIntegral()
{
}

template <typename T>
std::string TypeUnsignedIntegral<T>::typeName() const
{
    std::stringstream s;
    s << "uint";
    s << sizeof(T) * 8;
    return s.str();
}

template <typename T>
bool TypeUnsignedIntegral<T>::isIntegral() const
{
    return true;
}

template <typename T>
bool TypeUnsignedIntegral<T>::isUnsigned() const
{
    return true;
}

template <typename T>
bool TypeUnsignedIntegral<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
const T & TypeUnsignedIntegral<T>::defaultValue() const
{
    static T value = 0;

    return value;
}


} // namespace cppexpose
