
#pragma once


namespace cppexpose
{


template <typename Type, typename BaseType>
GenericComponent<Type, BaseType>::GenericComponent()
: AbstractGenericComponent<BaseType>()
{
}

template <typename Type, typename BaseType>
GenericComponent<Type, BaseType>::~GenericComponent()
{
}

template <typename Type, typename BaseType>
BaseType * GenericComponent<Type, BaseType>::createInstance() const
{
    return new Type();
}


} // namespace cppexpose
