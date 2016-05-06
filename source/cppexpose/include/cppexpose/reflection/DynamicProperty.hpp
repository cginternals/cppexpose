
#pragma once


#include <cppexpose/reflection/DynamicProperty.h>


namespace cppexpose
{


template <typename T>
template <typename... Args>
DynamicProperty<T>::DynamicProperty(PropertyGroup * parent, const std::string & name, Args&&... args)
: DirectValue<T>(std::forward<Args>(args)...)
, AbstractProperty(name, parent)
{
}

template <typename T>
DynamicProperty<T>::~DynamicProperty()
{
}

template <typename T>
AbstractTyped * DynamicProperty<T>::asTyped()
{
    return static_cast<AbstractTyped *>(this);
}

template <typename T>
const AbstractTyped * DynamicProperty<T>::asTyped() const
{
    return static_cast<const AbstractTyped *>(this);
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
