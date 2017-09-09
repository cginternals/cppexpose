
#pragma once


namespace cppexpose
{


template <typename T>
bool AbstractTyped::hasType() const
{
    return this->typeName() == BaseType<T>().typeName();
}


} // namespace cppexpose
