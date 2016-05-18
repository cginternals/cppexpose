
#pragma once


#include <cppexpose/typed/TypedSignedIntegral.hh>

#include <sstream>


namespace cppexpose
{


template <typename T, typename BASE>
TypedSignedIntegral<T, BASE>::TypedSignedIntegral()
{
}

template <typename T, typename BASE>
TypedSignedIntegral<T, BASE>::~TypedSignedIntegral()
{
}

template <typename T, typename BASE>
std::string TypedSignedIntegral<T, BASE>::typeName() const
{
    std::stringstream s;
    s << "int";
    s << sizeof(T) * 8;
    return s.str();
}

template <typename T, typename BASE>
bool TypedSignedIntegral<T, BASE>::isIntegral() const
{
    return true;
}

template <typename T, typename BASE>
bool TypedSignedIntegral<T, BASE>::isSignedIntegral() const
{
    return true;
}


} // namespace cppexpose
