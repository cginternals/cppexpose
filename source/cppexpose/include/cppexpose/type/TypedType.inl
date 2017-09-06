
#pragma once


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
