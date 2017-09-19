
#pragma once


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
const std::string & BaseTypeImplUnsignedIntegral<T>::typeName() const
{
    static const auto name = std::string("uint") + std::to_string(sizeof(T) * 8);

    return name;
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
