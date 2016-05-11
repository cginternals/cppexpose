
#pragma once


#include <cppexpose/reflection/DynamicProperty.h>


namespace cppexpose
{


template <typename T>
template <typename... Args>
DynamicProperty<T>::DynamicProperty(PropertyGroup * parent, const std::string & name, Args&&... args)
: DirectValue<T, AbstractProperty>(std::forward<Args>(args)...)
{
    this->initProperty(parent, name);
}

template <typename T>
DynamicProperty<T>::~DynamicProperty()
{
}

template <typename T>
bool DynamicProperty<T>::isGroup() const
{
    return false;
}

template <typename T>
void DynamicProperty<T>::onValueChanged(const T & value)
{
    this->valueChanged(value);
}


} // namespace cppexpose
