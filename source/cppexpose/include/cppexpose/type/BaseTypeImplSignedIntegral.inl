
#pragma once


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
const std::string & BaseTypeImplSignedIntegral<T>::typeName() const
{
    static const auto name = std::string("int") + std::to_string(sizeof(T) * 8);

    return name;
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
