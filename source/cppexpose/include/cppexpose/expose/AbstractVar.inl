
#pragma once


#include <cppexpose/expose/ValueStorage.h>


namespace cppexpose
{


template <typename Type>
class Var;


template <typename Type>
bool AbstractVar::hasType() const
{
    // [TODO]
    return false;
}

template <typename Type>
bool AbstractVar::canConvert() const
{
    return false;
}

template <typename Type>
Type AbstractVar::value() const
{
    Var<Type> var;
    var.fromVar(*this);
    return var.value();
}


} // namespace cppexpose