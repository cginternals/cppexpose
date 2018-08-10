
#pragma once


#include <cppexpose/expose/Property.h>


namespace cppexpose
{


template <typename Type>
Variant Variant::fromValue(const Type & value)
{
    return Variant(new Property<Type>(value));
}


} // namespace cppexpose
