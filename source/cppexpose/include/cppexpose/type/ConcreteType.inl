
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <typename T>
ConcreteType<T>::ConcreteType()
: Type(std::shared_ptr<BaseType<T>>(new BaseType<T>))
{
}

template <typename T>
ConcreteType<T>::~ConcreteType()
{
}

template <typename T>
const std::map<std::string, T> & ConcreteType<T>::namedValues() const
{
    return static_cast<BaseType<T> *>(m_type.get())->namedValues();
}

template <typename T>
void ConcreteType<T>::setNamedValues(const std::map<std::string, T> & namedValues)
{
    makeUnique();

    static_cast<BaseType<T> *>(m_type.get())->setNamedValues(namedValues);
}

template <typename T>
const T & ConcreteType<T>::defaultValue() const
{
    return static_cast<BaseType<T> *>(m_type.get())->defaultValue();
}

template <typename T>
const T & ConcreteType<T>::minimumValue() const
{
    return static_cast<BaseType<T> *>(m_type.get())->minimumValue();
}

template <typename T>
void ConcreteType<T>::setMinimumValue(const T & value)
{
    makeUnique();

    static_cast<BaseType<T> *>(m_type.get())->setMinimumValue(value);
}

template <typename T>
const T & ConcreteType<T>::maximumValue() const
{
    return static_cast<BaseType<T> *>(m_type.get())->maximumValue();
}

template <typename T>
void ConcreteType<T>::setMaximumValue(const T & value)
{
    makeUnique();

    static_cast<BaseType<T> *>(m_type.get())->setMaximumValue(value);
}

} // namespace cppexpose
