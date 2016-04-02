
#pragma once


#include <cppexpose/typed/TypedVariant.h>


namespace cppexpose
{


template <typename T>
TypedVariant<T>::TypedVariant()
{
}

template <typename T>
TypedVariant<T>::~TypedVariant()
{
}

template <typename T>
std::string TypedVariant<T>::typeName() const
{
    return "variant";
}

template <typename T>
bool TypedVariant<T>::isVariant() const
{
    return true;
}


} // namespace cppexpose
