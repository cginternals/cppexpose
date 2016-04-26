
#pragma once


#include <cppexpose/reflection/Property.h>

#include <cppexpose/typed/StoredValue.h>


namespace cppexpose
{


template <typename T>
template <typename... Args>
Property<T>::Property(const std::string & name, Args&&... args)
: AbstractProperty(name)
, m_value(new StoredValue<T>(std::forward<Args>(args)...))
{
}

template <typename T>
Property<T>::~Property()
{
    delete m_value;
}

template <typename T>
AbstractTyped * Property<T>::asTyped()
{
    return static_cast<AbstractTyped *>(this);
}

template <typename T>
const AbstractTyped * Property<T>::asTyped() const
{
    return static_cast<const AbstractTyped *>(this);
}

template <typename T>
bool Property<T>::isGroup() const
{
    return false;
}

template <typename T>
T Property<T>::value() const
{
    return m_value->value();
}

template <typename T>
void Property<T>::setValue(const T & value)
{
    m_value->setValue(value);
    this->onValueChanged(value);
}

template <typename T>
AbstractTyped * Property<T>::clone() const
{
    return m_value->clone();
}

template <typename T>
const std::type_info & Property<T>::type() const
{
    return m_value->type();
}

template <typename T>
std::string Property<T>::typeName() const
{
    return m_value->typeName();
}

template <typename T>
bool Property<T>::isReadOnly() const
{
    return m_value->isReadOnly();
}

template <typename T>
bool Property<T>::isComposite() const
{
    return m_value->isComposite();
}

template <typename T>
size_t Property<T>::numSubValues() const
{
    return m_value->numSubValues();
}

template <typename T>
AbstractTyped * Property<T>::subValue(size_t i)
{
    return m_value->subValue(i);
}

template <typename T>
bool Property<T>::isEnum() const
{
    return m_value->isEnum();
}

template <typename T>
bool Property<T>::isArray() const
{
    return m_value->isArray();
}

template <typename T>
bool Property<T>::isVariant() const
{
    return m_value->isVariant();
}

template <typename T>
bool Property<T>::isString() const
{
    return m_value->isString();
}

template <typename T>
bool Property<T>::isBool() const
{
    return m_value->isBool();
}

template <typename T>
bool Property<T>::isNumber() const
{
    return m_value->isNumber();
}

template <typename T>
bool Property<T>::isIntegral() const
{
    return m_value->isIntegral();
}

template <typename T>
bool Property<T>::isSignedIntegral() const
{
    return m_value->isSignedIntegral();
}

template <typename T>
bool Property<T>::isUnsignedIntegral() const
{
    return m_value->isUnsignedIntegral();
}

template <typename T>
bool Property<T>::isFloatingPoint() const
{
    return m_value->isFloatingPoint();
}

template <typename T>
Variant Property<T>::toVariant() const
{
    return m_value->toVariant();
}

template <typename T>
bool Property<T>::fromVariant(const Variant & value)
{
    return m_value->fromVariant(value);
}

template <typename T>
std::string Property<T>::toString() const
{
    return m_value->toString();
}

template <typename T>
bool Property<T>::fromString(const std::string & value)
{
    return m_value->fromString(value);
}

template <typename T>
bool Property<T>::toBool() const
{
    return m_value->toBool();
}

template <typename T>
bool Property<T>::fromBool(bool value)
{
    return m_value->fromBool(value);
}

template <typename T>
long long Property<T>::toLongLong() const
{
    return m_value->toLongLong();
}

template <typename T>
bool Property<T>::fromLongLong(long long value)
{
    return m_value->fromLongLong(value);
}

template <typename T>
unsigned long long Property<T>::toULongLong() const
{
    return m_value->toULongLong();
}

template <typename T>
bool Property<T>::fromULongLong(unsigned long long value)
{
    return m_value->fromULongLong(value);
}

template <typename T>
double Property<T>::toDouble() const
{
    return m_value->toDouble();
}

template <typename T>
bool Property<T>::fromDouble(double value)
{
    return m_value->fromDouble(value);
}

template <typename T>
void Property<T>::onValueChanged(const T & value)
{
    this->valueChanged(value);
}


} // namespace cppexpose
