
#pragma once


#include <cppexpose/variant/Variant.h>

#include <typeinfo>


/*
namespace
{


template <typename ValueType>
struct ConvertTo
{
    static ValueType convertTo(const cppexpose::Variant &) {
        return ValueType();
    }
};

template <>
struct ConvertTo<std::string>
{
    static std::string convertTo(const cppexpose::Variant & variant) {
        return variant.toJSON();
    }
};


} // namespace
*/


namespace cppexpose
{


template <typename T>
Variant Variant::fromValue(const T & value)
{
    Variant variant;
    variant.m_value = new DirectValue<T>(value);
    return variant;
}

template <typename T>
bool Variant::hasType() const
{
    if (!m_value) {
        return false;
    }

    return typeid(T) == this->type();
}

template <typename T>
bool Variant::canConvert() const
{
    /*
    if (!m_value) {
        return false;
    }

    return m_value->canConvert(typeid(T)) || hasType<T>();
    */
    return false;
}

template <typename T>
T Variant::value(const T & defaultValue) const
{
    /*
    // Type of variant is the wanted type
    if (m_value && typeid(T) == m_value->type()) {
        return static_cast<DirectValue<T> *>(m_value)->value();
    }

    // Variant has to be converted
    else if (m_value && m_value->canConvert(typeid(T))) {
        // Try to convert value
        T converted;
        if (m_value->convert(static_cast<void*>(&converted), typeid(T))) {
            return converted;
        }
    }

    // Variant map or array to string conversion
    else if (isMap() || isArray()) {
        return ConvertTo<T>::convertTo(*this);
    }
    */

    // No conversion possible
    return defaultValue;
}

template <typename T>
T * Variant::ptr()
{
    /*
    if (m_value && typeid(T) == this->type()) {
        return static_cast<DirectValue<T> *>(m_value)->ptr();
    } else {
        return nullptr;
    }
    */
    return nullptr;
}

template <typename T>
const T * Variant::ptr() const
{
    /*
    if (m_value && typeid(T) == this->type()) {
        return static_cast<const DirectValue<T> *>(m_value)->ptr();
    } else {
        return nullptr;
    }
    */
    return nullptr;
}


} // namespace cppexpose
