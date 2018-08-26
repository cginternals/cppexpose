
#pragma once


namespace cppexpose
{


template <typename Type>
AbstractTyped<Type>::AbstractTyped()
{
}

template <typename Type>
AbstractTyped<Type>::~AbstractTyped()
{
}

template <typename Type>
const Type * AbstractTyped<Type>::operator ->() const
{
    return this->get();
}

template <typename Type>
Type * AbstractTyped<Type>::operator ->()
{
    return this->get();
}


} // namespace cppexpose
