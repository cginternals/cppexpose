
#pragma once


#include <cppexpose/reflection/Object.h>


namespace cppexpose
{


template <typename T, typename BASE>
template <typename... Args>
Property<T, BASE>::Property(const std::string & name, Object * parent, Args&&... args)
: StoredValue<T, BASE>(std::forward<Args>(args)...)
{
    this->initProperty(name, parent, PropertyOwnership::None);
}

template <typename T, typename BASE>
Property<T, BASE>::~Property()
{
}

template <typename T, typename BASE>
bool Property<T, BASE>::isObject() const
{
    return false;
}

template <typename T, typename BASE>
void Property<T, BASE>::onValueChanged(const T & value)
{
    this->valueChanged(value);
}


} // namespace cppexpose
