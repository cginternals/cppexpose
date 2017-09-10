
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/value/InternalValue.h>


namespace cppexpose
{


template <typename T>
ExternalValue<T>::ExternalValue(
    std::function<T ()> getter
  , std::function<void(const T &)> setter)
: m_getter(getter)
, m_setter(setter)
{
}

template <typename T>
template <typename Obj>
ExternalValue<T>::ExternalValue(
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
ExternalValue<T>::~ExternalValue()
{
}

template <typename T>
std::unique_ptr<AbstractValueContainer> ExternalValue<T>::createCopy() const
{
    auto value = cppassist::make_unique<InternalValue<T>>();
    value->setValue(this->value());

    return std::move(value);
}

template <typename T>
std::string ExternalValue<T>::toString() const
{
    return this->m_type.baseType()->toString(this->value());
}

template <typename T>
bool ExternalValue<T>::fromString(const std::string & value)
{
    T tmp;

    if (!this->m_type.baseType()->fromString(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
bool ExternalValue<T>::toBool() const
{
    return this->m_type.baseType()->toBool(this->value());
}

template <typename T>
bool ExternalValue<T>::fromBool(bool value)
{
    T tmp;

    if (!this->m_type.baseType()->fromBool(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
long long ExternalValue<T>::toLongLong() const
{
    return this->m_type.baseType()->toLongLong(this->value());
}

template <typename T>
bool ExternalValue<T>::fromLongLong(long long value)
{
    T tmp;

    if (!this->m_type.baseType()->fromLongLong(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
unsigned long long ExternalValue<T>::toULongLong() const
{
    return this->m_type.baseType()->toULongLong(this->value());
}

template <typename T>
bool ExternalValue<T>::fromULongLong(unsigned long long value)
{
    T tmp;

    if (!this->m_type.baseType()->fromULongLong(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
double ExternalValue<T>::toDouble() const
{
    return this->m_type.baseType()->toDouble(this->value());
}

template <typename T>
bool ExternalValue<T>::fromDouble(double value)
{
    T tmp;

    if (!this->m_type.baseType()->fromDouble(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
T ExternalValue<T>::value() const
{
    return m_getter();
}

template <typename T>
void ExternalValue<T>::setValue(const T & value)
{
    m_setter(value);
    this->valueChanged(value);
}

template <typename T>
const T * ExternalValue<T>::ptr() const
{
    return nullptr;
}

template <typename T>
T * ExternalValue<T>::ptr()
{
    return nullptr;
}

template <typename T>
size_t ExternalValue<T>::numElements() const
{
    return this->m_type.baseType()->numElements(this->value());
}

template <typename T>
typename ExternalValue<T>::ElementType ExternalValue<T>::getElement(size_t i) const
{
    return this->m_type.baseType()->getElement(this->value(), i);
}

template <typename T>
void ExternalValue<T>::setElement(size_t i, ElementType value)
{
    T tmp = this->value();

    this->m_type.baseType()->setElement(tmp, i, value);
    setValue(tmp);
}

template <typename T>
void ExternalValue<T>::push(ElementType value)
{
    T tmp = this->value();

    this->m_type.baseType()->push(tmp, value);
    setValue(tmp);
}

template <typename T>
std::vector<std::string> ExternalValue<T>::keys() const
{
    return this->m_type.baseType()->keys(this->value());
}

template <typename T>
typename ExternalValue<T>::ElementType ExternalValue<T>::getElement(const std::string & key) const
{
    return this->m_type.baseType()->getElement(this->value(), key);
}

template <typename T>
void ExternalValue<T>::setElement(const std::string & key, ElementType value)
{
    T tmp = this->value();

    this->m_type.baseType()->setElement(tmp, key, value);
    setValue(tmp);
}


} // namespace cppexpose