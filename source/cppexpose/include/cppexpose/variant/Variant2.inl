
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/type/AbstractValue.h>


namespace cppexpose
{


template <typename T>
Variant2 Variant2::fromValue(const T & value)
{
    Variant2 variant;
    variant.m_value = cppassist::make_unique<Value<T>>(value);
    return variant;
}

template <typename T>
bool Variant2::hasType() const
{
    if (!m_value) {
        return false;
    }

    return typeid(T) == m_value->typeInfo();
}

template <typename T>
bool Variant2::canConvert() const
{
    if (m_value) {
        return m_value->canConvert<T>();
    }

    return false;
}

template <typename T>
T Variant2::value() const
{
    // Type of variant is the wanted type
    if (m_value && typeid(T) == m_value->typeInfo())
    {
        return static_cast<Value<T> *>(m_value.get())->value();
    }

    // Variant has to be converted
    else if (m_value && m_value->canConvert<T>())
    {
        return m_value->value<T>();
    }

    // No conversion possible
    else
    {
        return Type<T>().defaultValue();
    }
}

template <typename T>
T * Variant2::ptr()
{
    if (m_value && typeid(T) == m_value->typeInfo()) {
        return static_cast<Value<T> *>(m_value.get())->ptr();
    } else {
        return nullptr;
    }
}

template <typename T>
const T * Variant2::ptr() const
{
    if (m_value && typeid(T) == m_value->typeInfo()) {
        return static_cast<const Value<T> *>(m_value.get())->ptr();
    } else {
        return nullptr;
    }
}


} // namespace cppexpose
