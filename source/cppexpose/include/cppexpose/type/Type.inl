
#pragma once


namespace cppexpose
{


// Type<T>
template <typename T>
Type<T>::Type()
{
}

template <typename T>
Type<T>::~Type()
{
}

template <typename T>
bool Type<T>::isConst() const
{
    return false;
}


// Type<const T>
template <typename T>
Type<const T>::Type()
{
}

template <typename T>
Type<const T>::~Type()
{
}

template <typename T>
bool Type<const T>::isConst() const
{
    return true;
}


} // namespace cppexpose
