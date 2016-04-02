
#pragma once


#include <cppexpose/typed/TypedString.h>


namespace cppexpose
{


template <typename T>
TypedString<T>::TypedString()
{
}

template <typename T>
TypedString<T>::~TypedString()
{
}

template <typename T>
std::string TypedString<T>::typeName() const
{
    return "string";
}

template <typename T>
bool TypedString<T>::isString() const
{
    return true;
}


} // namespace cppexpose
