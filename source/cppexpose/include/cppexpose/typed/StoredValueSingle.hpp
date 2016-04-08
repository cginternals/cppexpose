
#pragma once


#include <cppexpose/typed/StoredValueSingle.h>


namespace cppexpose
{


// Read/write type
template <typename T>
StoredValueSingle<T>::StoredValueSingle(
    std::function<T ()> getter
  , std::function<void(const T &)> setter)
: m_getter(getter)
, m_setter(setter)
{
}

template <typename T>
StoredValueSingle<T>::~StoredValueSingle()
{
}

template <typename T>
AbstractTyped * StoredValueSingle<T>::clone() const
{
    return new StoredValueSingle<T>(m_getter, m_setter);
}

template <typename T>
T StoredValueSingle<T>::value() const
{
    return m_getter();
}

template <typename T>
void StoredValueSingle<T>::setValue(const T & value)
{
    m_setter(value);
}

template <typename T>
StoredValueSingle<T>::StoredValueSingle(const std::function<T ()> & getter)
: m_getter(getter)
{
}


// Read-only type
template <typename T>
StoredValueSingle<const T>::StoredValueSingle(std::function<T ()> getter)
: StoredValueSingle<T>::StoredValueSingle(getter)
{
}

template <typename T>
StoredValueSingle<const T>::~StoredValueSingle()
{
}

template <typename T>
AbstractTyped * StoredValueSingle<const T>::clone() const
{
    return new StoredValueSingle<const T>(this->m_getter);
}

template <typename T>
bool StoredValueSingle<const T>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T>
void StoredValueSingle<const T>::setValue(const T &)
{
    // Read-only!
}


} // namespace cppexpose
