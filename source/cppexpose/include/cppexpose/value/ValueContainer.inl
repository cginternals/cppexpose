
#pragma once


#include <cppexpose/type/Type.h>
#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


template <typename T>
ValueContainer<T>::ValueContainer()
{
}

template <typename T>
ValueContainer<T>::~ValueContainer()
{
}

template <typename T>
const Type & ValueContainer<T>::type() const
{
    return m_type;
}

template <typename T>
Type & ValueContainer<T>::type()
{
    return m_type;
}

template <typename T>
const Type & ValueContainer<T>::elementType() const
{
    return m_type.elementType();
}

template <typename T>
Type & ValueContainer<T>::elementType()
{
    return m_type.elementType();
}

template <typename T>
std::string ValueContainer<T>::typeName() const
{
    return m_type.typeName();
}

template <typename T>
bool ValueContainer<T>::isNull() const
{
    return m_type.isNull();
}

template <typename T>
bool ValueContainer<T>::isType() const
{
    return m_type.isType();
}

template <typename T>
bool ValueContainer<T>::isConst() const
{
    return m_type.isConst();
}

template <typename T>
bool ValueContainer<T>::isArray() const
{
    return m_type.isArray();
}

template <typename T>
bool ValueContainer<T>::isDynamicArray() const
{
    return m_type.isDynamicArray();
}

template <typename T>
bool ValueContainer<T>::isMap() const
{
    return m_type.isMap();
}

template <typename T>
bool ValueContainer<T>::isBoolean() const
{
    return m_type.isBoolean();
}

template <typename T>
bool ValueContainer<T>::isNumber() const
{
    return m_type.isNumber();
}

template <typename T>
bool ValueContainer<T>::isIntegral() const
{
    return m_type.isIntegral();
}

template <typename T>
bool ValueContainer<T>::isUnsigned() const
{
    return m_type.isUnsigned();
}

template <typename T>
bool ValueContainer<T>::isFloatingPoint() const
{
    return m_type.isFloatingPoint();
}

template <typename T>
bool ValueContainer<T>::isString() const
{
    return m_type.isString();
}

template <typename T>
Variant ValueContainer<T>::element(size_t i) const
{
    return Variant::fromValue<ElementType>(this->elementValue(i));
}

template <typename T>
void ValueContainer<T>::setElement(size_t i, const Variant & value)
{
    this->setElementValue(i, value.value<ElementType>());
}

template <typename T>
void ValueContainer<T>::pushElement(const Variant & value)
{
    this->push(value.value<ElementType>());
}

template <typename T>
Variant ValueContainer<T>::element(const std::string & key) const
{
    return Variant::fromValue<ElementType>(this->elementValue(key));
}

template <typename T>
void ValueContainer<T>::setElement(const std::string & key, const Variant & value)
{
    this->setElementValue(key, value.value<ElementType>());
}


} // namespace cppexpose
