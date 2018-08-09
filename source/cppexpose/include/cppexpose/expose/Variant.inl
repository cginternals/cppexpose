
#pragma once


namespace cppexpose
{


template <typename Type>
Variant Variant::fromValue(const Type & value)
{
    return Variant(new Var<Type>(value));
}


} // namespace cppexpose
