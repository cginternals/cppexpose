
#pragma once


#include <cppexpose/typed/DirectValueSingle.h>


namespace cppexpose
{


// Read/write type
template <typename T>
DirectValueSingle<T>::DirectValueSingle()
{
}

template <typename T>
DirectValueSingle<T>::DirectValueSingle(const T & value)
: m_value(value)
{
}

template <typename T>
DirectValueSingle<T>::~DirectValueSingle()
{
}

template <typename T>
const T * DirectValueSingle<T>::ptr() const
{
    return &m_value;
}

template <typename T>
T * DirectValueSingle<T>::ptr()
{
    return &m_value;
}

template <typename T>
AbstractTyped * DirectValueSingle<T>::clone() const
{
    return new DirectValueSingle<T>(m_value);
}

template <typename T>
T DirectValueSingle<T>::value() const
{
    return m_value;
}

template <typename T>
void DirectValueSingle<T>::setValue(const T & value)
{
    m_value = value;
    this->onValueChanged(m_value);
}


// Read-only type
template <typename T>
DirectValueSingle<const T>::DirectValueSingle()
{
}

template <typename T>
DirectValueSingle<const T>::DirectValueSingle(const T & value)
: DirectValueSingle<T>::DirectValueSingle(value)
{
}

template <typename T>
DirectValueSingle<const T>::~DirectValueSingle()
{
}

template <typename T>
AbstractTyped * DirectValueSingle<const T>::clone() const
{
    return new DirectValueSingle<const T>(this->m_value);
}

template <typename T>
bool DirectValueSingle<const T>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T>
void DirectValueSingle<const T>::setValue(const T &)
{
    // Read-only!
}


} // namespace cppexpose
