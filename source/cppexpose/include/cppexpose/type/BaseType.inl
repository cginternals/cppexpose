
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


// BaseType<T>
template <typename T>
BaseType<T>::BaseType()
{
}

template <typename T>
BaseType<T>::~BaseType()
{
}

template <typename T>
std::shared_ptr<AbstractBaseType> BaseType<T>::createCopy() const
{
    return std::shared_ptr<AbstractBaseType>(new BaseType<T>);
}

template <typename T>
bool BaseType<T>::isConst() const
{
    return false;
}


// BaseType<const T>
template <typename T>
BaseType<const T>::BaseType()
{
}

template <typename T>
BaseType<const T>::~BaseType()
{
}

template <typename T>
std::shared_ptr<AbstractBaseType> BaseType<const T>::createCopy() const
{
    return std::shared_ptr<AbstractBaseType>(new BaseType<const T>);
}

template <typename T>
bool BaseType<const T>::isConst() const
{
    return true;
}


} // namespace cppexpose
