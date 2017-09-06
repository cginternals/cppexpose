
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


// TypedType<T>
template <typename T>
TypedType<T>::TypedType()
{
}

template <typename T>
TypedType<T>::~TypedType()
{
}

template <typename T>
std::unique_ptr<AbstractType> TypedType<T>::createCopy() const
{
    return cppassist::make_unique<TypedType<T>>();
}

template <typename T>
bool TypedType<T>::isConst() const
{
    return false;
}

template <typename T>
const AbstractType & TypedType<T>::type() const
{
    return this->elementType();
}


// TypedType<const T>
template <typename T>
TypedType<const T>::TypedType()
{
}

template <typename T>
TypedType<const T>::~TypedType()
{
}

template <typename T>
std::unique_ptr<AbstractType> TypedType<const T>::createCopy() const
{
    return cppassist::make_unique<TypedType<const T>>();
}

template <typename T>
bool TypedType<const T>::isConst() const
{
    return true;
}

template <typename T>
const AbstractType & TypedType<const T>::type() const
{
    return this->elementType();
}


} // namespace cppexpose
