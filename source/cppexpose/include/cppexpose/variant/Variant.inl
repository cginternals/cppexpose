
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/value/AbstractValueContainer.h>


namespace cppexpose
{


template <typename T>
class InternalValue;


template <typename T>
Variant Variant::fromValue(const T & value)
{
    Variant variant;
    variant.m_value = cppassist::make_unique<InternalValue<T>>(value);

    return variant;
}

template <typename T>
bool Variant::hasType() const
{
    if (!m_value) {
        return false;
    }

    return BaseType<T>().typeName() == typeName();
}

template <typename T>
bool Variant::canConvert() const
{
    if (m_value) {
        return m_value->canConvert<T>();
    }

    return false;
}

template <typename T>
T Variant::value() const
{
    // Type of variant is the wanted type
    if (m_value && this->hasType<T>())
    {
        return static_cast<InternalValue<T> *>(m_value.get())->value();
    }

    // Variant has to be converted
    else if (m_value && m_value->canConvert<T>())
    {
        return m_value->value<T>();
    }

    // No conversion possible
    else
    {
        return BaseType<T>().defaultValue();
    }
}

template <typename T>
T * Variant::ptr()
{
    if (m_value && this->hasType<T>()) {
        return static_cast<InternalValue<T> *>(m_value.get())->ptr();
    } else {
        return nullptr;
    }
}

template <typename T>
const T * Variant::ptr() const
{
    if (m_value && this->hasType<T>()) {
        return static_cast<const InternalValue<T> *>(m_value.get())->ptr();
    } else {
        return nullptr;
    }
}


} // namespace cppexpose
