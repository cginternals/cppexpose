
#pragma once


#include <cppexpose/reflection/PropertyGroup.h>


namespace cppexpose
{


template <typename T>
Property<T> * PropertyGroup::property(const std::string & path)
{
    // Get typed property, will be nullptr on error
    return this->property(path)->as<Property<Type>>();
}

template <typename T>
const Property<T> * PropertyGroup::property(const std::string & path) const
{
    // Get typed property, will be nullptr on error
    return this->property(path)->as<Property<Type>>();
}

template <typename T, typename... Args>
Property<T> * PropertyGroup::addProperty(const std::string & name, Args&&... args)
{
    // Create new property
    auto property = new Property<Type>(name, std::forward<Args>(args)...);
    if (this->addProperty(property))
    {
        return property;
    }

    // Error, delete property and return
    delete property;
    return nullptr;
}


} // namespace cppexpose
