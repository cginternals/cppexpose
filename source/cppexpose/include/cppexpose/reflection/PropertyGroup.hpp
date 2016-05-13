
#pragma once


#include <cppexpose/reflection/PropertyGroup.h>


namespace cppexpose
{


template <typename T>
DynamicProperty<T> * PropertyGroup::addDynamicProperty(const std::string & name, const T & value)
{
    // Reject properties that have no name or whose name already exists
    if (name == "" || this->propertyExists(name))
    {
        return nullptr;
    }

    // Create property
    auto * property = new DynamicProperty<T>(this, name, value);
    takeOwnership(property);

    return property;
}


} // namespace cppexpose
