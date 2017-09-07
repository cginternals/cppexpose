
#pragma once


#include <cppexpose/type/TypedType.h>


namespace cppexpose
{


template <typename T>
AbstractTypedValue<T>::AbstractTypedValue()
{
}

template <typename T>
AbstractTypedValue<T>::~AbstractTypedValue()
{
}

template <typename T>
const Type & AbstractTypedValue<T>::type() const
{
    static Type type(m_type.createCopy());
    return type;
}

template <typename T>
Type & AbstractTypedValue<T>::type()
{
    static Type type(m_type.createCopy());
    return type;
}

template <typename T>
const Type & AbstractTypedValue<T>::elementType() const
{
    static Type type(m_type.createCopy());
    return type.elementType();
}

template <typename T>
Type & AbstractTypedValue<T>::elementType()
{
    static Type type(m_type.createCopy());
    return type.elementType();
}

template <typename T>
bool AbstractTypedValue<T>::hasSymbolicNames() const
{
    return m_type.hasSymbolicNames();
}

template <typename T>
std::vector<std::string> AbstractTypedValue<T>::symbolicNames() const
{
    return m_type.symbolicNames();
}

template <typename T>
std::string AbstractTypedValue<T>::typeName() const
{
    return m_type.typeName();
}

template <typename T>
bool AbstractTypedValue<T>::isNull() const
{
    return m_type.isNull();
}

template <typename T>
bool AbstractTypedValue<T>::isConst() const
{
    return m_type.isConst();
}

template <typename T>
bool AbstractTypedValue<T>::isArray() const
{
    return m_type.isArray();
}

template <typename T>
bool AbstractTypedValue<T>::isDynamicArray() const
{
    return m_type.isDynamicArray();
}

template <typename T>
bool AbstractTypedValue<T>::isMap() const
{
    return m_type.isMap();
}

template <typename T>
bool AbstractTypedValue<T>::isBoolean() const
{
    return m_type.isBoolean();
}

template <typename T>
bool AbstractTypedValue<T>::isNumber() const
{
    return m_type.isNumber();
}

template <typename T>
bool AbstractTypedValue<T>::isIntegral() const
{
    return m_type.isIntegral();
}

template <typename T>
bool AbstractTypedValue<T>::isUnsigned() const
{
    return m_type.isUnsigned();
}

template <typename T>
bool AbstractTypedValue<T>::isFloatingPoint() const
{
    return m_type.isFloatingPoint();
}

template <typename T>
bool AbstractTypedValue<T>::isString() const
{
    return m_type.isString();
}

template <typename T>
bool AbstractTypedValue<T>::isType() const
{
    return m_type.isType();
}


} // namespace cppexpose
