
#pragma once


#include <cppexpose/typed/Typed.h>

#include <typeinfo>


namespace cppexpose
{


template <typename T>
Typed<T>::Typed()
{
}

template <typename T>
Typed<T>::~Typed()
{
}

template <typename T>
const std::type_info & Typed<T>::type() const
{
    return typeid(T);
}

template <typename T>
bool Typed<T>::isReadOnly() const
{
    return false;
}


} // namespace cppexpose
