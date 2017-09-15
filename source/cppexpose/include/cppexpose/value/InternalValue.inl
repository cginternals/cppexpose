
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
std::unique_ptr<AbstractValueContainer> InternalValue<T>::createCopy() const
{
    auto value = cppassist::make_unique<InternalValue<T>>();
    value->setValue(this->value());

    return std::move(value);
}

template <typename T>
std::string InternalValue<T>::toString() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toString(m_value);
}

template <typename T>
bool InternalValue<T>::fromString(const std::string & value)
{
    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromString(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
bool InternalValue<T>::toBool() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toBool(m_value);
}

template <typename T>
bool InternalValue<T>::fromBool(bool value)
{
    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromBool(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
long long InternalValue<T>::toLongLong() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toLongLong(m_value);
}

template <typename T>
bool InternalValue<T>::fromLongLong(long long value)
{
    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromLongLong(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
unsigned long long InternalValue<T>::toULongLong() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toULongLong(m_value);
}

template <typename T>
bool InternalValue<T>::fromULongLong(unsigned long long value)
{
    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromULongLong(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
double InternalValue<T>::toDouble() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toDouble(m_value);
}

template <typename T>
bool InternalValue<T>::fromDouble(double value)
{
    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromDouble(m_value, value)) {
        return false;
    }

    this->valueChanged(m_value);
    return true;
}

template <typename T>
Variant InternalValue<T>::toVariant() const
{
    return Variant::fromValue(m_value);
}

template <typename T>
bool InternalValue<T>::fromVariant(const Variant & variant)
{
    if (!variant.canConvert<T>())
    {
        m_value = T();
        return false;
    }

    m_value = variant.value<T>();
    return true;
}

template <typename T>
size_t InternalValue<T>::numElements() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->numElements(m_value);
}

template <typename T>
std::vector<std::string> InternalValue<T>::keys() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->keys(m_value);
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
typename InternalValue<T>::ElementType InternalValue<T>::elementValue(size_t i) const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->getElement(m_value, i);
}

template <typename T>
void InternalValue<T>::setElementValue(size_t i, ElementType value)
{
    static_cast<BaseType<T> *>(this->m_type.baseType())->setElement(m_value, i, value);
    this->valueChanged(m_value);
}

template <typename T>
void InternalValue<T>::push(ElementType value)
{
    static_cast<BaseType<T> *>(this->m_type.baseType())->push(m_value, value);
    this->valueChanged(m_value);
}

template <typename T>
typename InternalValue<T>::ElementType InternalValue<T>::elementValue(const std::string & key) const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->getElement(m_value, key);
}

template <typename T>
void InternalValue<T>::setElementValue(const std::string & key, ElementType value)
{
    static_cast<BaseType<T> *>(this->m_type.baseType())->setElement(m_value, key, value);
    this->valueChanged(m_value);
}


} // namespace cppexpose
