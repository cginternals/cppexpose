
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <typename Type, typename... Args>
bool Object::createProperty(const std::string & name, Args&&... args)
{
    auto value = cppassist::make_unique<Var<Type>>(std::forward<Args>(args)...);
    return addProperty(name, std::move(value));
}


} // namespace cppexpose
