
#pragma once


#include <cppexpose/typed/TypedBool.h>


namespace cppexpose
{


template <typename T>
TypedBool<T>::TypedBool()
{
}

template <typename T>
TypedBool<T>::~TypedBool()
{
}

template <typename T>
std::string TypedBool<T>::typeName() const
{
    return "bool";
}

template <typename T>
bool TypedBool<T>::isBool() const
{
    return true;
}


} // namespace cppexpose
