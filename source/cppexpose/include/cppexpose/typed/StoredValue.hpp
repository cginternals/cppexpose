
#pragma once


#include <cppexpose/typed/StoredValue.h>


namespace cppexpose
{


template <typename T>
template <typename... Args>
StoredValue<T>::StoredValue(Args&&... args)
: BaseType(std::forward<Args>(args)...)
{
}

template <typename T>
StoredValue<T>::StoredValue(const T & value)
: BaseType(value)
{
}

template <typename T>
StoredValue<T>::~StoredValue()
{
}


} // namespace cppexpose
