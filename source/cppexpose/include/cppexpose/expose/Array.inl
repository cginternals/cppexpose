
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <typename Type, typename... Args>
bool Array::createElement(Args&&... args)
{
    auto property = cppassist::make_unique<Property<Type>>(std::forward<Args>(args)...);
    return this->push(std::move(property));
}


} // namespace cppexpose
