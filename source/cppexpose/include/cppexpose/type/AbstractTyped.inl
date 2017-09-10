
#pragma once


namespace cppexpose
{


template <typename T>
bool AbstractTyped::hasType() const
{
    return *this->baseType() == BaseType<T>();
}


} // namespace cppexpose
