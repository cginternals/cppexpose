
#pragma once


#include <cppexpose/typed/DirectValueArray.hh>


namespace cppexpose
{


// Read/write type
template <typename T>
DirectValueArray<T>::DirectValueArray()
{
}

template <typename T>
DirectValueArray<T>::DirectValueArray(const T & value)
: m_value(value)
{
}

template <typename T>
DirectValueArray<T>::~DirectValueArray()
{
}

template <typename T>
AbstractTyped * DirectValueArray<T>::clone() const
{
    return new DirectValueArray<T>(m_value);
}

template <typename T>
T DirectValueArray<T>::value() const
{
    return m_value;
}

template <typename T>
void DirectValueArray<T>::setValue(const T & value)
{
    m_value = value;
    this->onValueChanged(m_value);
}

template <typename T>
const T * DirectValueArray<T>::ptr() const
{
    return &m_value;
}

template <typename T>
T * DirectValueArray<T>::ptr()
{
    return &m_value;
}

template <typename T>
typename DirectValueArray<T>::ElementType DirectValueArray<T>::getElement(size_t i) const
{
    return m_value[i];
}

template <typename T>
void DirectValueArray<T>::setElement(size_t i, const typename DirectValueArray<T>::ElementType & value)
{
    m_value[i] = value;
    this->onValueChanged(m_value);
}


// Read-only type
template <typename T>
DirectValueArray<const T>::DirectValueArray()
{
}

template <typename T>
DirectValueArray<const T>::DirectValueArray(const T & value)
: DirectValueArray<T>::DirectValueArray(value)
{
}

template <typename T>
DirectValueArray<const T>::~DirectValueArray()
{
}

template <typename T>
AbstractTyped * DirectValueArray<const T>::clone() const
{
    return new DirectValueArray<const T>(this->m_value);
}

template <typename T>
bool DirectValueArray<const T>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T>
void DirectValueArray<const T>::setValue(const T &)
{
    // Read-only!
}

template <typename T>
T * DirectValueArray<const T>::ptr()
{
    // Read-only!
    return nullptr;
}

template <typename T>
void DirectValueArray<const T>::setElement(size_t, const typename DirectValueArray<T>::ElementType &)
{
    // Read-only!
}


} // namespace cppexpose
