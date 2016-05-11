
#pragma once


#include <cppexpose/reflection/PropertyGroup.h>
#include <cppexpose/reflection/Property.h>
#include <cppexpose/reflection/DynamicProperty.h>

#include <typeinfo>


namespace cppexpose
{


template <typename T>
Property<T> * PropertyGroup::property(const std::string & path)
{
    AbstractProperty * prop = this->property(path);

    if (prop && prop->type() == typeid(T)) {
        return static_cast<Property<T> *>(this->property(path));
    }

    return nullptr;
}

template <typename T>
const Property<T> * PropertyGroup::property(const std::string & path) const
{
    const AbstractProperty * prop = this->property(path);

    if (prop && prop->type() == typeid(T)) {
        return static_cast<const Property<T> *>(this->property(path));
    }

    return nullptr;
}


} // namespace cppexpose
