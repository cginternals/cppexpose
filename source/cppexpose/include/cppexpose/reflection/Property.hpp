
#pragma once


#include <cppexpose/reflection/Property.h>

#include <cppexpose/reflection/PropertyGroup.h>


namespace cppexpose
{


template <typename T>
template <typename... Args>
Property<T>::Property(PropertyGroup * parent, const std::string & name, Args&&... args)
: StoredValue<T>(std::forward<Args>(args)...)
, AbstractProperty(name)
{
    parent->addProperty(this, Ownership::Self);
}

template <typename T>
Property<T>::~Property()
{
}

template <typename T>
AbstractTyped * Property<T>::asTyped()
{
    return static_cast<AbstractTyped *>(this);
}

template <typename T>
const AbstractTyped * Property<T>::asTyped() const
{
    return static_cast<const AbstractTyped *>(this);
}

template <typename T>
bool Property<T>::isGroup() const
{
    return false;
}

template <typename T>
void Property<T>::onValueChanged(const T & value)
{
    this->valueChanged(value);
}


} // namespace cppexpose
