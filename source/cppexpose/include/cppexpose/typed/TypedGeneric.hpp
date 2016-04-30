
#pragma once


#include <cppexpose/typed/TypedGeneric.hh>


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
