
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose_plugin
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
std::unique_ptr<BaseType> GenericComponent<Type, BaseType>::createInstance() const
{
    return cppassist::make_unique<Type>();
}


} // namespace cppexpose_plugin
