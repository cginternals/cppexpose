
#pragma once


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
const AbstractType & AbstractTypedValue<T>::type() const
{
    return m_type;
}

template <typename T>
const std::type_info & AbstractTypedValue<T>::typeInfo() const
{
    return m_type.typeInfo();
}

template <typename T>
std::string AbstractTypedValue<T>::typeName() const
{
    return m_type.typeName();
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


} // namespace cppexpose
