
#pragma once


#include <cppexpose/typed/StoredValueArray.h>


namespace cppexpose
{


// Read/write type
template <typename T>
StoredValueArray<T>::StoredValueArray(
    std::function<T ()> getter
  , std::function<void(const T &)> setter
  , std::function<ElementType (int)> elementGetter
  , std::function<void(int, const ElementType &)> elementSetter)
: m_getter(getter)
, m_setter(setter)
, m_elementGetter(elementGetter)
, m_elementSetter(elementSetter)
{
}

template <typename T>
StoredValueArray<T>::~StoredValueArray()
{
}

template <typename T>
AbstractTyped * StoredValueArray<T>::clone() const
{
    return new StoredValueArray<T>(m_getter, m_setter, m_elementGetter, m_elementSetter);
}

template <typename T>
T StoredValueArray<T>::value() const
{
    return m_getter();
}

template <typename T>
void StoredValueArray<T>::setValue(const T & value)
{
    m_setter(value);
}

template <typename T>
typename StoredValueArray<T>::ElementType StoredValueArray<T>::getElement(size_t i) const
{
    return m_elementGetter(i);
}

template <typename T>
void StoredValueArray<T>::setElement(size_t i, const typename StoredValueArray<T>::ElementType & value)
{
    m_elementSetter(i, value);
}

template <typename T>
StoredValueArray<T>::StoredValueArray(
    std::function<T ()> getter
  , std::function<ElementType (int)> elementGetter)
: m_getter(getter)
, m_elementGetter(elementGetter)
{
}


// Read-only type
template <typename T>
StoredValueArray<const T>::StoredValueArray(
    std::function<T ()> getter
  , std::function<typename StoredValueArray<T>::ElementType (int)> elementGetter)
: StoredValueArray<T>::StoredValueArray(getter, elementGetter)
{
}

template <typename T>
StoredValueArray<const T>::~StoredValueArray()
{
}

template <typename T>
AbstractTyped * StoredValueArray<const T>::clone() const
{
    return new StoredValueArray<const T>(
      this->m_getter,
      this->m_setter,
      this->m_elementGetter,
      this->m_elementSetter
    );
}

template <typename T>
bool StoredValueArray<const T>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T>
void StoredValueArray<const T>::setValue(const T &)
{
    // Read-only!
}

template <typename T>
void StoredValueArray<const T>::setElement(size_t, const typename StoredValueArray<T>::ElementType &)
{
    // Read-only!
}


} // namespace cppexpose
