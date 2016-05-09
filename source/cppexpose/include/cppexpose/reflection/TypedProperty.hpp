
#pragma once


#include <cppexpose/reflection/TypedProperty.h>


namespace cppexpose
{


template <typename T>
TypedProperty<T>::TypedProperty(PropertyGroup * parent, const std::string & name)
: AbstractProperty(name, parent)
{
}

template <typename T>
TypedProperty<T>::~TypedProperty()
{
}

template <typename T>
bool TypedProperty<T>::isGroup() const
{
    return false;
}


} // namespace cppexpose
