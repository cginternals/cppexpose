
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/type/Value.h>


namespace cppexpose
{


template <typename T>
ManagedValue<T>::ManagedValue(
    std::function<T ()> getter
  , std::function<void(const T &)> setter)
: m_getter(getter)
, m_setter(setter)
{
}

template <typename T>
template <typename Obj>
ManagedValue<T>::ManagedValue(
    Obj * obj,
    typename SetterFunctions<T, Obj>::getter g,
    typename SetterFunctions<T, Obj>::setter s)
{
    typename SetterFunctions<T, Obj>::getter getter = g;
    typename SetterFunctions<T, Obj>::setter setter = s;

    m_getter = [obj, getter] () -> T
    {
        return (obj->*getter)();
    };

    m_setter = [obj, setter] (const T & value)
    {
        (obj->*setter)(value);
    };
}

template <typename T>
ManagedValue<T>::~ManagedValue()
{
}

template <typename T>
std::unique_ptr<AbstractValue> ManagedValue<T>::createCopy() const
{
    auto value = cppassist::make_unique<Value<T>>();
    value->setValue(this->value());

    return std::move(value);
}

template <typename T>
std::string ManagedValue<T>::toString() const
{
    return this->m_type.toString(this->value());
}

template <typename T>
bool ManagedValue<T>::fromString(const std::string & value)
{
    T tmp;

    if (!this->m_type.fromString(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
bool ManagedValue<T>::toBool() const
{
    return this->m_type.toBool(this->value());
}

template <typename T>
bool ManagedValue<T>::fromBool(bool value)
{
    T tmp;

    if (!this->m_type.fromBool(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
long long ManagedValue<T>::toLongLong() const
{
    return this->m_type.toLongLong(this->value());
}

template <typename T>
bool ManagedValue<T>::fromLongLong(long long value)
{
    T tmp;

    if (!this->m_type.fromLongLong(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
unsigned long long ManagedValue<T>::toULongLong() const
{
    return this->m_type.toULongLong(this->value());
}

template <typename T>
bool ManagedValue<T>::fromULongLong(unsigned long long value)
{
    T tmp;

    if (!this->m_type.fromULongLong(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
double ManagedValue<T>::toDouble() const
{
    return this->m_type.toDouble(this->value());
}

template <typename T>
bool ManagedValue<T>::fromDouble(double value)
{
    T tmp;

    if (!this->m_type.fromDouble(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
T ManagedValue<T>::value() const
{
    return m_getter();
}

template <typename T>
void ManagedValue<T>::setValue(const T & value)
{
    m_setter(value);
    this->valueChanged(value);
}

template <typename T>
const T * ManagedValue<T>::ptr() const
{
    return nullptr;
}

template <typename T>
T * ManagedValue<T>::ptr()
{
    return nullptr;
}

template <typename T>
size_t ManagedValue<T>::numElements() const
{
    return this->m_type.numElements(this->value());
}

template <typename T>
typename ManagedValue<T>::ElementType ManagedValue<T>::getElement(size_t i) const
{
    return this->m_type.getElement(this->value(), i);
}

template <typename T>
void ManagedValue<T>::setElement(size_t i, ElementType value)
{
    T tmp = this->value();

    this->m_type.setElement(tmp, i, value);
    setValue(tmp);
}

template <typename T>
void ManagedValue<T>::push(ElementType value)
{
    T tmp = this->value();

    this->m_type.push(tmp, value);
    setValue(tmp);
}

template <typename T>
std::vector<std::string> ManagedValue<T>::keys() const
{
    return this->m_type.keys(this->value());
}

template <typename T>
typename ManagedValue<T>::ElementType ManagedValue<T>::getElement(const std::string & key) const
{
    return this->m_type.getElement(this->value(), key);
}

template <typename T>
void ManagedValue<T>::setElement(const std::string & key, ElementType value)
{
    T tmp = this->value();

    this->m_type.setElement(tmp, key, value);
    setValue(tmp);
}


} // namespace cppexpose
