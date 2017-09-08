
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <typename T>
InternalValue<T>::InternalValue()
: m_value(this->m_type.defaultValue())
{
}

template <typename T>
InternalValue<T>::InternalValue(const T & value)
: m_value(value)
{
}

template <typename T>
InternalValue<T>::~InternalValue()
{
}

template <typename T>
std::unique_ptr<AbstractValue> InternalValue<T>::createCopy() const
{
    auto value = cppassist::make_unique<InternalValue<T>>();
    value->setValue(this->value());

    return std::move(value);
}

template <typename T>
std::string InternalValue<T>::toString() const
{
    return this->m_type.toString(m_value);
}

template <typename T>
bool InternalValue<T>::fromString(const std::string & value)
{
    if (!this->m_type.fromString(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
bool InternalValue<T>::toBool() const
{
    return this->m_type.toBool(m_value);
}

template <typename T>
bool InternalValue<T>::fromBool(bool value)
{
    if (!this->m_type.fromBool(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
long long InternalValue<T>::toLongLong() const
{
    return this->m_type.toLongLong(m_value);
}

template <typename T>
bool InternalValue<T>::fromLongLong(long long value)
{
    if (!this->m_type.fromLongLong(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
unsigned long long InternalValue<T>::toULongLong() const
{
    return this->m_type.toULongLong(m_value);
}

template <typename T>
bool InternalValue<T>::fromULongLong(unsigned long long value)
{
    if (!this->m_type.fromULongLong(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
double InternalValue<T>::toDouble() const
{
    return this->m_type.toDouble(m_value);
}

template <typename T>
bool InternalValue<T>::fromDouble(double value)
{
    if (!this->m_type.fromDouble(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
T InternalValue<T>::value() const
{
    return m_value;
}

template <typename T>
void InternalValue<T>::setValue(const T & value)
{
    m_value = value;
    this->valueChanged(m_value);
}

template <typename T>
const T * InternalValue<T>::ptr() const
{
    return &m_value;
}

template <typename T>
T * InternalValue<T>::ptr()
{
    return &m_value;
}

template <typename T>
size_t InternalValue<T>::numElements() const
{
    return this->m_type.numElements(m_value);
}

template <typename T>
typename InternalValue<T>::ElementType InternalValue<T>::getElement(size_t i) const
{
    return this->m_type.getElement(m_value, i);
}

template <typename T>
void InternalValue<T>::setElement(size_t i, ElementType value)
{
    this->m_type.setElement(m_value, i, value);
    this->valueChanged(m_value);
}

template <typename T>
void InternalValue<T>::push(ElementType value)
{
    this->m_type.push(m_value, value);
    this->valueChanged(m_value);
}

template <typename T>
std::vector<std::string> InternalValue<T>::keys() const
{
    return this->m_type.keys(m_value);
}

template <typename T>
typename InternalValue<T>::ElementType InternalValue<T>::getElement(const std::string & key) const
{
    return this->m_type.getElement(m_value, key);
}

template <typename T>
void InternalValue<T>::setElement(const std::string & key, ElementType value)
{
    this->m_type.setElement(m_value, key, value);
    this->valueChanged(m_value);
}


} // namespace cppexpose
