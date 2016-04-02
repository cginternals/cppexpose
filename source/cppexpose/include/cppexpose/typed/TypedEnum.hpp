
#pragma once


#include <cppexpose/typed/TypedEnum.h>


namespace cppexpose
{


template <typename T>
TypedEnum<T>::TypedEnum()
{
}

template <typename T>
TypedEnum<T>::~TypedEnum()
{
}

template <typename T>
std::string TypedEnum<T>::typeName() const
{
    return "enum";
}


} // namespace cppexpose
