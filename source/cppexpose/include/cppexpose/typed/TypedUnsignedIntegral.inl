
#pragma once


#include <sstream>


namespace cppexpose
{


template <typename T, typename BASE>
TypedUnsignedIntegral<T, BASE>::TypedUnsignedIntegral()
{
}

template <typename T, typename BASE>
TypedUnsignedIntegral<T, BASE>::~TypedUnsignedIntegral()
{
}

template <typename T, typename BASE>
std::string TypedUnsignedIntegral<T, BASE>::typeName() const
{
    std::stringstream s;
    s << "uint";
    s << sizeof(T) * 8;
    return s.str();
}

template <typename T, typename BASE>
bool TypedUnsignedIntegral<T, BASE>::isIntegral() const
{
    return true;
}

template <typename T, typename BASE>
bool TypedUnsignedIntegral<T, BASE>::isUnsignedIntegral() const
{
    return true;
}


} // namespace cppexpose
