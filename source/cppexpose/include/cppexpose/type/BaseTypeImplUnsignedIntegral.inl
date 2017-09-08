
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T>
BaseTypeImplUnsignedIntegral<T>::BaseTypeImplUnsignedIntegral()
{
}

template <typename T>
BaseTypeImplUnsignedIntegral<T>::~BaseTypeImplUnsignedIntegral()
{
}

template <typename T>
std::string BaseTypeImplUnsignedIntegral<T>::typeName() const
{
    std::stringstream s;
    s << "uint";
    s << sizeof(T) * 8;
    return s.str();
}

template <typename T>
bool BaseTypeImplUnsignedIntegral<T>::isIntegral() const
{
    return true;
}

template <typename T>
bool BaseTypeImplUnsignedIntegral<T>::isUnsigned() const
{
    return true;
}

template <typename T>
bool BaseTypeImplUnsignedIntegral<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
const T & BaseTypeImplUnsignedIntegral<T>::defaultValue() const
{
    static T value = 0;

    return value;
}


} // namespace cppexpose
