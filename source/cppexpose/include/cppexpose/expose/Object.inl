
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <typename Type, typename... Args>
bool Object::createProperty(const std::string & name, Args&&... args)
{
    auto property = cppassist::make_unique<Property<Type>>(std::forward<Args>(args)...);
    return addProperty(name, std::move(property));
}


} // namespace cppexpose
