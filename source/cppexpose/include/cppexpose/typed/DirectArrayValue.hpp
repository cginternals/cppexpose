
#pragma once


#include <cppexpose/typed/DirectArrayValue.h>


namespace cppexpose
{


// Read/write type
template <typename T>
DirectArrayValue<T>::DirectArrayValue()
{
}

template <typename T>
DirectArrayValue<T>::DirectArrayValue(const T & value)
: m_value(value)
{
}

template <typename T>
DirectArrayValue<T>::~DirectArrayValue()
{
}

template <typename T>
AbstractTyped * DirectArrayValue<T>::clone() const
{
    return new DirectArrayValue<T>(m_value);
}

template <typename T>
T DirectArrayValue<T>::value() const
{
    return m_value;
}

template <typename T>
void DirectArrayValue<T>::setValue(const T & value)
{
    m_value = value;
}

template <typename T>
typename DirectArrayValue<T>::ElementType DirectArrayValue<T>::getElement(size_t i) const
{
    return m_value[i];
}

template <typename T>
void DirectArrayValue<T>::setElement(size_t i, const typename DirectArrayValue<T>::ElementType & value)
{
    m_value[i] = value;
}


// Read-only type
template <typename T>
DirectArrayValue<const T>::DirectArrayValue()
{
}

template <typename T>
DirectArrayValue<const T>::DirectArrayValue(const T & value)
: DirectArrayValue<T>::DirectArrayValue(value)
{
}

template <typename T>
DirectArrayValue<const T>::~DirectArrayValue()
{
}

template <typename T>
AbstractTyped * DirectArrayValue<const T>::clone() const
{
    return new DirectArrayValue<const T>(this->m_value);
}

template <typename T>
bool DirectArrayValue<const T>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T>
void DirectArrayValue<const T>::setValue(const T &)
{
    // Read-only!
}

template <typename T>
void DirectArrayValue<const T>::setElement(size_t, const typename DirectArrayValue<T>::ElementType &)
{
    // Read-only!
}


} // namespace cppexpose
