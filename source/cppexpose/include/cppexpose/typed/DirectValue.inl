
#pragma once


namespace cppexpose
{


template <typename T, typename BASE>
DirectValue<T, BASE>::DirectValue()
: BaseType()
{
}

template <typename T, typename BASE>
DirectValue<T, BASE>::DirectValue(const T & value)
: BaseType(value)
{
}

template <typename T, typename BASE>
DirectValue<T, BASE>::~DirectValue()
{
}


} // namespace cppexpose
