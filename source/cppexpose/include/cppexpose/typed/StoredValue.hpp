
#pragma once


#include <cppexpose/typed/StoredValue.hh>


namespace cppexpose
{


template <typename T, typename BASE>
template <typename... Args>
StoredValue<T, BASE>::StoredValue(Args&&... args)
: BaseType(std::forward<Args>(args)...)
{
}

template <typename T, typename BASE>
StoredValue<T, BASE>::StoredValue(const T & value)
: BaseType(value)
{
}

template <typename T, typename BASE>
StoredValue<T, BASE>::~StoredValue()
{
}


} // namespace cppexpose
