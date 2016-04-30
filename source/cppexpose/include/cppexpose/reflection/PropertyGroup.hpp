
#pragma once


#include <cppexpose/reflection/PropertyGroup.h>
#include <cppexpose/reflection/Property.h>

#include <typeinfo>


namespace cppexpose
{


template <typename T>
Property<T> * PropertyGroup::property(const std::string & path)
{
    AbstractProperty * prop = this->property(path);

    if (prop && prop->asTyped()->type() == typeid(T)) {
        return static_cast<Property<T> *>(this->property(path));
    }

    return nullptr;
}

template <typename T>
const Property<T> * PropertyGroup::property(const std::string & path) const
{
    const AbstractProperty * prop = this->property(path);

    if (prop && prop->asTyped()->type() == typeid(T)) {
        return static_cast<const Property<T> *>(this->property(path));
    }

    return nullptr;
}

template <typename T, typename... Args>
Property<T> * PropertyGroup::addProperty(const std::string & name, Args&&... args)
{
    // Create new property
    auto property = new Property<T>(name, std::forward<Args>(args)...);
    if (this->addProperty(property))
    {
        return property;
    }

    // Error, delete property and return
    delete property;
    return nullptr;
}


} // namespace cppexpose
