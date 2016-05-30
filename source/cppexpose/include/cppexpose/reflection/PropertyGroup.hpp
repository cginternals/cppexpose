
#pragma once


#include <cppexpose/reflection/PropertyGroup.h>


namespace cppexpose
{


template <typename T>
DynamicProperty<T> * PropertyGroup::createDynamicProperty(const std::string & name, const T & value)
{
    // Reject properties that have no name or whose name already exists
    if (name == "" || this->propertyExists(name))
    {
        return nullptr;
    }

    // Create property and add it to the group
    auto * property = new DynamicProperty<T>(name, nullptr, value);
    this->addProperty(property, PropertyOwnership::Parent);

    // Return property
    return property;
}


} // namespace cppexpose
