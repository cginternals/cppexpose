
#pragma once


#include <cppexpose/reflection/DynamicProperty.h>


namespace cppexpose
{


template <typename T, typename BASE>
template <typename... Args>
DynamicProperty<T, BASE>::DynamicProperty(const std::string & name, PropertyGroup * parent, Args&&... args)
: DirectValue<T, BASE>(std::forward<Args>(args)...)
{
    this->initProperty(name, parent, PropertyOwnership::None);
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
