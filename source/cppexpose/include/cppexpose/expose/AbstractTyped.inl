
#pragma once


namespace cppexpose
{


template <typename Type>
template <typename... Args>
AbstractTyped<Type>::AbstractTyped(Args&&... args)
: AbstractVar(std::forward<Args>(args)...)
{
}

template <typename Type>
AbstractTyped<Type>::~AbstractTyped()
{
}


} // namespace cppexpose
