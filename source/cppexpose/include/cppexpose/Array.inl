
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <typename Type, typename... Args>
bool Array::createElement(Args&&... args)
{
    auto value = cppassist::make_unique<Var<Type>>(std::forward<Args>(args)...);
    return this->push(std::move(value));
}


} // namespace cppexpose
