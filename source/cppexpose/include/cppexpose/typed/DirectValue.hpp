
#pragma once


#include <cppexpose/typed/DirectValue.h>


namespace cppexpose
{


// Read/write type
template <typename T>
DirectValue<T>::DirectValue()
{
}

template <typename T>
DirectValue<T>::~DirectValue()
{
}

template <typename T>
T DirectValue<T>::value() const
{
    return m_value;
}

template <typename T>
void DirectValue<T>::setValue(const T & value)
{
    m_value = value;
}


// Read-only type
template <typename T>
DirectValue<const T>::DirectValue()
{
}

template <typename T>
DirectValue<const T>::~DirectValue()
{
}

template <typename T>
bool DirectValue<const T>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T>
void DirectValue<const T>::setValue(const T &)
{
    // Read-only!
}


} // namespace cppexpose
