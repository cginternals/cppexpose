
#pragma once


#include <typeinfo>

#include <cppexpose/base/template_helpers.h>
#include <cppexpose/typed/DirectValue.hh>


namespace cppexpose
{


template <typename T>
struct ConvertVariant
{
    static bool canConvert()
    {
        return false;
    }

    static T convertTo(const Variant &)
    {
        return T();
    }
};

template <>
struct ConvertVariant<std::string>
{
    static bool canConvert()
    {
        return true;
    }

    static std::string convertTo(const Variant & variant)
    {
        return variant.toJSON();
    }
};


template <typename T>
Variant Variant::fromValue(const T & value)
{
    Variant variant;
    variant.m_value = cppassist::make_unique<DirectValue<T>>(value);
    return variant;
}

template <typename T>
bool Variant::hasType() const
{
    if (!m_value) {
        return false;
    }

    return typeid(T) == m_value->type();
}

template <typename T>
bool Variant::canConvert() const
{
    if (isVariantMap() || isVariantArray())
    {
        return ConvertVariant<T>::canConvert();
    }

    else if (m_value) {
        return m_value->canConvert<T>();
    }

    return false;
}

template <typename T>
T Variant::value(const T & defaultValue) const
{
    // Type of variant is the wanted type
    if (m_value && typeid(T) == m_value->type())
    {
        return reinterpret_cast<DirectValue<T> *>(m_value.get())->value();
    }

    // Variant map or array to string conversion
    else if (isVariantMap() || isVariantArray())
    {
        return ConvertVariant<T>::convertTo(*this);
    }

    // Variant has to be converted
    else if (m_value && m_value->canConvert<T>())
    {
        return m_value->convert<T>(defaultValue);
    }

    // No conversion possible
    return defaultValue;
}

template <typename T>
T * Variant::ptr()
{
    if (m_value && typeid(T) == m_value->type()) {
        return static_cast<DirectValue<T> *>(m_value.get())->ptr();
    } else {
        return nullptr;
    }
}

template <typename T>
const T * Variant::ptr() const
{
    if (m_value && typeid(T) == m_value->type()) {
        return static_cast<const DirectValue<T> *>(m_value.get())->ptr();
    } else {
        return nullptr;
    }
}


} // namespace cppexpose
