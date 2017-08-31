
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <typename T>
Value<T>::Value()
: m_value(this->m_type.defaultValue())
{
}

template <typename T>
Value<T>::Value(const T & value)
: m_value(value)
{
}

template <typename T>
Value<T>::~Value()
{
}

template <typename T>
std::unique_ptr<AbstractValue> Value<T>::createCopy() const
{
    auto value = cppassist::make_unique<Value<T>>();
    value->setValue(this->value());

    return std::move(value);
}

template <typename T>
std::string Value<T>::toString() const
{
    return this->m_type.toString(m_value);
}

template <typename T>
bool Value<T>::fromString(const std::string & value)
{
    return this->m_type.fromString(m_value, value);
}

template <typename T>
bool Value<T>::toBool() const
{
    return this->m_type.toBool(m_value);
}

template <typename T>
bool Value<T>::fromBool(bool value)
{
    return this->m_type.fromBool(m_value, value);
}

template <typename T>
long long Value<T>::toLongLong() const
{
    return this->m_type.toLongLong(m_value);
}

template <typename T>
bool Value<T>::fromLongLong(long long value)
{
    return this->m_type.fromLongLong(m_value, value);
}

template <typename T>
unsigned long long Value<T>::toULongLong() const
{
    return this->m_type.toULongLong(m_value);
}

template <typename T>
bool Value<T>::fromULongLong(unsigned long long value)
{
    return this->m_type.fromULongLong(m_value, value);
}

template <typename T>
double Value<T>::toDouble() const
{
    return this->m_type.toDouble(m_value);
}

template <typename T>
bool Value<T>::fromDouble(double value)
{
    return this->m_type.fromDouble(m_value, value);
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

template <typename T>
std::vector<std::string> Value<T>::keys() const
{
    return this->m_type.keys(m_value);
}

template <typename T>
typename Value<T>::ElementType Value<T>::getElement(const std::string & key) const
{
    return this->m_type.getElement(m_value, key);
}

template <typename T>
void Value<T>::setElement(const std::string & key, ElementType value)
{
    this->m_type.setElement(m_value, key, value);
}


} // namespace cppexpose
