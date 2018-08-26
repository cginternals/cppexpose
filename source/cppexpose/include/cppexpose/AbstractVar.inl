
#pragma once


namespace cppexpose
{


template <typename Type>
class Var;


template <typename Type>
bool AbstractVar::canConvert() const
{
    return false;
}

template <typename Type>
Type AbstractVar::convert() const
{
    Var<Type> var;
    var.fromVar(*this);
    return var.value();
}

template <typename Type>
Type AbstractVar::asTyped()
{
    return static_cast<Type>(this->innermost());
}

template <typename Type>
Type AbstractVar::asTyped() const
{
    return static_cast<Type>(this->innermost());
}


} // namespace cppexpose
