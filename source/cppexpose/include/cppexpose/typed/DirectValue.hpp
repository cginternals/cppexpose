
#pragma once


#include <cppexpose/typed/DirectValue.hh>


namespace cppexpose
{


template <typename T>
DirectValue<T>::DirectValue()
: BaseType()
{
}

template <typename T>
DirectValue<T>::DirectValue(const T & value)
: BaseType(value)
{
}

template <typename T>
DirectValue<T>::~DirectValue()
{
}


} // namespace cppexpose
