
#pragma once


namespace cppexpose
{


// Type<T>
template <typename T>
Type<T>::Type()
{
}

template <typename T>
Type<T>::~Type()
{
}

template <typename T>
bool Type<T>::isConst() const
{
    return false;
}

template <typename T>
const AbstractType & Type<T>::type() const
{
    return this->elementType();
}


// Type<const T>
template <typename T>
Type<const T>::Type()
{
}

template <typename T>
Type<const T>::~Type()
{
}

template <typename T>
bool Type<const T>::isConst() const
{
    return true;
}

template <typename T>
const AbstractType & Type<const T>::type() const
{
    return this->elementType();
}


} // namespace cppexpose
