
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/value/InternalValue.h>


namespace cppexpose
{


template <typename T>
ExternalValue<T>::ExternalValue(
    std::function<T ()> getter
  , std::function<void(const T &)> setter
  , std::function<ElementType (size_t)> arrayGetter
  , std::function<void(size_t, const ElementType &)> arraySetter
  , std::function<ElementType (const std::string &)> mapGetter
  , std::function<void(const std::string &, const ElementType &)> mapSetter)
: m_getter(getter)
, m_setter(setter)
, m_arrayGetter(arrayGetter)
, m_arraySetter(arraySetter)
, m_mapGetter(mapGetter)
, m_mapSetter(mapSetter)
{
}

template <typename T>
template <typename Obj>
ExternalValue<T>::ExternalValue(
    Obj * obj,
    typename SetterFunctions<T, ElementType, Obj>::getter g
  , typename SetterFunctions<T, ElementType, Obj>::setter s
  , typename SetterFunctions<T, ElementType, Obj>::arrayGetter ag
  , typename SetterFunctions<T, ElementType, Obj>::arraySetter as
  , typename SetterFunctions<T, ElementType, Obj>::mapGetter mg
  , typename SetterFunctions<T, ElementType, Obj>::mapSetter ms)
{
    typename SetterFunctions<T, ElementType, Obj>::getter getter = g;
    typename SetterFunctions<T, ElementType, Obj>::setter setter = s;
    typename SetterFunctions<T, ElementType, Obj>::arrayGetter arrayGetter = ag;
    typename SetterFunctions<T, ElementType, Obj>::arraySetter arraySetter = as;
    typename SetterFunctions<T, ElementType, Obj>::mapGetter mapGetter = mg;
    typename SetterFunctions<T, ElementType, Obj>::mapSetter mapSetter = ms;

    m_getter = [obj, getter] () -> T
    {
        return (obj->*getter)();
    };

    m_setter = [obj, setter] (const T & value)
    {
        (obj->*setter)(value);
    };

    if (arrayGetter && arraySetter)
    {
        m_arrayGetter = [obj, arrayGetter] (size_t i) -> ElementType
        {
            return (obj->*arrayGetter)(i);
        };

        m_arraySetter = [obj, arraySetter] (size_t i, const ElementType & value)
        {
            (obj->*arraySetter)(i, value);
        };
    }

    if (mapGetter && mapSetter)
    {
        m_mapGetter = [obj, mapGetter] (const std::string & key) -> ElementType
        {
            return (obj->*mapGetter)(key);
        };

        m_mapSetter = [obj, mapSetter] (const std::string & key, const ElementType & value)
        {
            (obj->*mapSetter)(key, value);
        };
    }
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
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toString(this->value());
}

template <typename T>
bool ExternalValue<T>::fromString(const std::string & value)
{
    T tmp;

    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromString(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
bool ExternalValue<T>::toBool() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toBool(this->value());
}

template <typename T>
bool ExternalValue<T>::fromBool(bool value)
{
    T tmp;

    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromBool(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
long long ExternalValue<T>::toLongLong() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toLongLong(this->value());
}

template <typename T>
bool ExternalValue<T>::fromLongLong(long long value)
{
    T tmp;

    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromLongLong(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
unsigned long long ExternalValue<T>::toULongLong() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toULongLong(this->value());
}

template <typename T>
bool ExternalValue<T>::fromULongLong(unsigned long long value)
{
    T tmp;

    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromULongLong(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
double ExternalValue<T>::toDouble() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->toDouble(this->value());
}

template <typename T>
bool ExternalValue<T>::fromDouble(double value)
{
    T tmp;

    if (!static_cast<BaseType<T> *>(this->m_type.baseType())->fromDouble(tmp, value)) {
        return false;
    }

    setValue(tmp);
    return true;
}

template <typename T>
size_t ExternalValue<T>::numElements() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->numElements(this->value());
}

template <typename T>
std::vector<std::string> ExternalValue<T>::keys() const
{
    return static_cast<const BaseType<T> *>(this->m_type.baseType())->keys(this->value());
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
typename ExternalValue<T>::ElementType ExternalValue<T>::elementValue(size_t i) const
{
    if (m_arrayGetter)
    {
        return m_arrayGetter(i);
    }
    else
    {
        return static_cast<const BaseType<T> *>(this->m_type.baseType())->getElement(this->value(), i);
    }
}

template <typename T>
void ExternalValue<T>::setElementValue(size_t i, ElementType value)
{
    if (m_arraySetter)
    {
        m_arraySetter(i, value);
    }
    else
    {
        T tmp = this->value();
        static_cast<BaseType<T> *>(this->m_type.baseType())->setElement(tmp, i, value);
        setValue(tmp);
    }
}

template <typename T>
void ExternalValue<T>::push(ElementType value)
{
    T tmp = this->value();
    static_cast<BaseType<T> *>(this->m_type.baseType())->push(tmp, value);
    setValue(tmp);
}

template <typename T>
typename ExternalValue<T>::ElementType ExternalValue<T>::elementValue(const std::string & key) const
{
    if (m_mapGetter)
    {
        return m_mapGetter(key);
    }
    else
    {
        return static_cast<const BaseType<T> *>(this->m_type.baseType())->getElement(this->value(), key);
    }
}

template <typename T>
void ExternalValue<T>::setElementValue(const std::string & key, ElementType value)
{
    if (m_mapSetter)
    {
        m_mapSetter(key, value);
    }
    else
    {
        T tmp = this->value();
        static_cast<BaseType<T> *>(this->m_type.baseType())->setElement(tmp, key, value);
        setValue(tmp);
    }
}


} // namespace cppexpose
