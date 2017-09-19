
#pragma once


namespace cppexpose
{


template <typename T>
bool AbstractTyped::hasType() const
{
    static BaseType<T> baseType;

    return *this->baseType() == baseType;
}


} // namespace cppexpose
