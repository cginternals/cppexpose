
#pragma once


#include <cppexpose/typed/DirectValueSingle.hh>


namespace cppexpose
{


// Read/write type
template <typename T, typename BASE>
DirectValueSingle<T, BASE>::DirectValueSingle()
{
}

template <typename T, typename BASE>
DirectValueSingle<T, BASE>::DirectValueSingle(const T & value)
: m_value(value)
{
}

template <typename T, typename BASE>
DirectValueSingle<T, BASE>::~DirectValueSingle()
{
}

template <typename T, typename BASE>
AbstractTyped * DirectValueSingle<T, BASE>::clone() const
{
    return new DirectValueSingle<T, BASE>(m_value);
}

template <typename T, typename BASE>
T DirectValueSingle<T, BASE>::value() const
{
    return m_value;
}

template <typename T, typename BASE>
void DirectValueSingle<T, BASE>::setValue(const T & value)
{
    m_value = value;
    this->onValueChanged(m_value);
}

template <typename T, typename BASE>
const T * DirectValueSingle<T, BASE>::ptr() const
{
    return &m_value;
}

template <typename T, typename BASE>
T * DirectValueSingle<T, BASE>::ptr()
{
    return &m_value;
}


// Read-only type
template <typename T, typename BASE>
DirectValueSingle<const T, BASE>::DirectValueSingle()
{
}

template <typename T, typename BASE>
DirectValueSingle<const T, BASE>::DirectValueSingle(const T & value)
: DirectValueSingle<T, BASE>::DirectValueSingle(value)
{
}

template <typename T, typename BASE>
DirectValueSingle<const T, BASE>::~DirectValueSingle()
{
}

template <typename T, typename BASE>
AbstractTyped * DirectValueSingle<const T, BASE>::clone() const
{
    return new DirectValueSingle<const T, BASE>(this->m_value);
}

template <typename T, typename BASE>
bool DirectValueSingle<const T, BASE>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T, typename BASE>
void DirectValueSingle<const T, BASE>::setValue(const T &)
{
    // Read-only!
}

template <typename T, typename BASE>
T * DirectValueSingle<const T, BASE>::ptr()
{
    // Read-only!
    return nullptr;
}


} // namespace cppexpose
