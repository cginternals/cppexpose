
#pragma once


namespace cppexpose
{


template <typename T>
Value<T>::Value()
{
}

template <typename T>
Value<T>::~Value()
{
}

template <typename T>
T Value<T>::value() const
{
    return m_value;
}

template <typename T>
void Value<T>::setValue(const T & value)
{
    m_value = value;
}

template <typename T>
const T * Value<T>::ptr() const
{
    return &m_value;
}

template <typename T>
T * Value<T>::ptr()
{
    return &m_value;
}

template <typename T>
size_t Value<T>::numElements() const
{
    return this->m_type.numElements(m_value);
}

template <typename T>
typename Value<T>::ElementType Value<T>::getElement(size_t i) const
{
    return this->m_type.getElement(m_value, i);
}

template <typename T>
void Value<T>::setElement(size_t i, ElementType value)
{
    this->m_type.setElement(m_value, i, value);
}

template <typename T>
void Value<T>::push(ElementType value)
{
    this->m_type.push(m_value, value);
}


} // namespace cppexpose
