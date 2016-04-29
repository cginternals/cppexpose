
#pragma once


#include <cppexpose/typed/TypedGeneric.h>


namespace cppexpose
{


template <typename T>
TypedGeneric<T>::TypedGeneric()
{
}

template <typename T>
TypedGeneric<T>::~TypedGeneric()
{
}

template <typename T>
std::string TypedGeneric<T>::typeName() const
{
    return "unknown";
}


} // namespace cppexpose
