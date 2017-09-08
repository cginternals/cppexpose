
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/type/BaseType.h>


namespace cppexpose
{


template <typename T>
ConcreteType<T>::ConcreteType()
: Type(std::shared_ptr<BaseType<T>>(new BaseType<T>))
{
}

template <typename T>
ConcreteType<T>::~ConcreteType()
{
}


} // namespace cppexpose
