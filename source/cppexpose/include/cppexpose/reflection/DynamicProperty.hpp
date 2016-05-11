
#pragma once


#include <cppexpose/reflection/DynamicProperty.h>


namespace cppexpose
{


template <typename T, typename BASE>
template <typename... Args>
DynamicProperty<T, BASE>::DynamicProperty(PropertyGroup * parent, const std::string & name, Args&&... args)
: DirectValue<T, BASE>(std::forward<Args>(args)...)
{
    this->initProperty(parent, name);
}

template <typename T, typename BASE>
DynamicProperty<T, BASE>::~DynamicProperty()
{
}

template <typename T, typename BASE>
bool DynamicProperty<T, BASE>::isGroup() const
{
    return false;
}

template <typename T, typename BASE>
void DynamicProperty<T, BASE>::onValueChanged(const T & value)
{
    this->valueChanged(value);
}


} // namespace cppexpose
