
#pragma once


#include <cppexpose/reflection/Property.h>

#include <cppexpose/reflection/PropertyGroup.h>


namespace cppexpose
{


template <typename T, typename BASE>
template <typename... Args>
Property<T, BASE>::Property(const std::string & name, PropertyGroup * parent, Args&&... args)
: StoredValue<T, BASE>(std::forward<Args>(args)...)
{
    this->initProperty(name, parent);
}

template <typename T, typename BASE>
Property<T, BASE>::~Property()
{
}

template <typename T, typename BASE>
bool Property<T, BASE>::isGroup() const
{
    return false;
}

template <typename T, typename BASE>
void Property<T, BASE>::onValueChanged(const T & value)
{
    this->valueChanged(value);
}


} // namespace cppexpose
