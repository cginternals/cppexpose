
#pragma once


#include <cppexpose/typed/StoredValue.h>


namespace cppexpose
{


// Read/write type
template <typename T>
StoredValue<T>::StoredValue(
    std::function<T ()> getter
  , std::function<void(const T &)> setter)
: m_getter(getter)
, m_setter(setter)
{
}

template <typename T>
StoredValue<T>::~StoredValue()
{
}

template <typename T>
AbstractTyped * StoredValue<T>::clone() const
{
    return new StoredValue<T>(m_getter, m_setter);
}

template <typename T>
T StoredValue<T>::value() const
{
    return m_getter();
}

template <typename T>
void StoredValue<T>::setValue(const T & value)
{
    m_setter(value);
}

template <typename T>
StoredValue<T>::StoredValue(const std::function<T ()> & getter)
: m_getter(getter)
{
}


// Read-only type
template <typename T>
StoredValue<const T>::StoredValue(std::function<T ()> getter)
: StoredValue<T>::StoredValue(getter)
{
}

template <typename T>
StoredValue<const T>::~StoredValue()
{
}

template <typename T>
AbstractTyped * StoredValue<const T>::clone() const
{
    return new StoredValue<const T>(this->m_getter);
}

template <typename T>
bool StoredValue<const T>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T>
void StoredValue<const T>::setValue(const T &)
{
    // Read-only!
}


} // namespace cppexpose
