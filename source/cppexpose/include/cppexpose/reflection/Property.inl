
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/value/InternalValue.h>
#include <cppexpose/value/ExternalValue.h>


namespace cppexpose
{


template <typename T>
Property<T>::Property(const std::string & name, Object * parent)
: AbstractProperty(name, parent)
, m_value(new InternalValue<T>)
{
    m_value->valueChanged.connect([this] (const T & value) {
        this->valueChanged(value);
    });
}

template <typename T>
Property<T>::Property(const std::string & name, Object * parent, const T & value)
: AbstractProperty(name, parent)
, m_value(new InternalValue<T>(value))
{
    m_value->valueChanged.connect([this] (const T & value) {
        this->valueChanged(value);
    });
}

template <typename T>
template <typename ... Arguments>
Property<T>::Property(const std::string & name, Object * parent, Arguments && ... arguments)
: AbstractProperty(name, parent)
, m_value(new ExternalValue<T>(arguments...))
{
}

template <typename T>
Property<T>::~Property()
{
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
}

template <typename T>
const T * Property<T>::ptr() const
{
    return m_value->ptr();
}

template <typename T>
T * Property<T>::ptr()
{
    return m_value->ptr();
}

template <typename T>
const Type & Property<T>::type() const
{
    return m_value->type();
}

template <typename T>
Type & Property<T>::type()
{
    return m_value->type();
}

template <typename T>
const AbstractBaseType * Property<T>::baseType() const
{
    return m_value->baseType();
}

template <typename T>
AbstractBaseType * Property<T>::baseType()
{
    return m_value->baseType();
}

template <typename T>
const Type & Property<T>::elementType() const
{
    return m_value->elementType();
}

template <typename T>
Type & Property<T>::elementType()
{
    return m_value->elementType();
}

template <typename T>
std::string Property<T>::typeName() const
{
    return m_value->typeName();
}

template <typename T>
bool Property<T>::isNull() const
{
    return m_value->isNull();
}

template <typename T>
bool Property<T>::isType() const
{
    return m_value->isType();
}

template <typename T>
bool Property<T>::isConst() const
{
    return m_value->isConst();
}

template <typename T>
bool Property<T>::isArray() const
{
    return m_value->isArray();
}

template <typename T>
bool Property<T>::isDynamicArray() const
{
    return m_value->isDynamicArray();
}

template <typename T>
bool Property<T>::isMap() const
{
    return m_value->isMap();
}

template <typename T>
bool Property<T>::isBoolean() const
{
    return m_value->isBoolean();
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
bool Property<T>::isUnsigned() const
{
    return m_value->isUnsigned();
}

template <typename T>
bool Property<T>::isFloatingPoint() const
{
    return m_value->isFloatingPoint();
}

template <typename T>
bool Property<T>::isString() const
{
    return m_value->isString();
}

template <typename T>
std::unique_ptr<AbstractValueContainer> Property<T>::createCopy() const
{
    return m_value->createCopy();
}

template <typename T>
bool Property<T>::compareTypeAndValue(const AbstractValueContainer & value) const
{
    return m_value->compareTypeAndValue(value);
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
size_t Property<T>::numElements() const
{
    return m_value->numElements();
}

template <typename T>
Variant Property<T>::element(size_t i) const
{
    return m_value->element(i);
}

template <typename T>
void Property<T>::setElement(size_t i, const Variant & value)
{
    m_value->setElement(i, value);
}

template <typename T>
void Property<T>::pushElement(const Variant & value)
{
    m_value->pushElement(value);
}

template <typename T>
std::vector<std::string> Property<T>::keys() const
{
    return m_value->keys();
}

template <typename T>
Variant Property<T>::element(const std::string & key) const
{
    return m_value->element(key);
}

template <typename T>
void Property<T>::setElement(const std::string & key, const Variant & value)
{
    m_value->setElement(key, value);
}

template <typename T>
bool Property<T>::isObject() const
{
    return false;
}


} // namespace cppexpose
