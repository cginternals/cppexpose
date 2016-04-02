
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
bool TypedArray<T, Size, BaseType>::isReadOnly() const
{
    return false;
}


} // namespace cppexpose
