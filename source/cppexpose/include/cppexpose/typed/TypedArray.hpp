
#pragma once


#include <cppexpose/typed/TypedArray.h>


namespace cppexpose
{


template <typename T, size_t Size, typename BaseType>
TypedArray<T, Size, BaseType>::TypedArray()
{
}

template <typename T, size_t Size, typename BaseType>
TypedArray<T, Size, BaseType>::~TypedArray()
{
}

template <typename T, size_t Size, typename BaseType>
std::string TypedArray<T, Size, BaseType>::typeName() const
{
    return "array";
}

template <typename T, size_t Size, typename BaseType>
bool TypedArray<T, Size, BaseType>::isArray() const
{
    return true;
}


} // namespace cppexpose
