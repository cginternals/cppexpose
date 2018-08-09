
#pragma once


namespace cppexpose
{


template <typename Type, typename BaseClass>
template <typename... Args>
AbstractTyped<Type, BaseClass>::AbstractTyped(Args&&... args)
: BaseClass(std::forward<Args>(args)...)
{
}

template <typename Type, typename BaseClass>
AbstractTyped<Type, BaseClass>::~AbstractTyped()
{
}


} // namespace cppexpose
