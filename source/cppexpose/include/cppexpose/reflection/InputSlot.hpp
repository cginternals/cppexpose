
#pragma once


#include <cppexpose/reflection/InputSlot.h>

#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


template <typename T>
InputSlot<T>::InputSlot(PropertyGroup * parent, const std::string & name)
: TypedProperty<T>(parent, name)
, m_source(nullptr)
{
}

template <typename T>
InputSlot<T>::~InputSlot()
{
}

template <typename T>
bool InputSlot<T>::isConnected() const
{
    return false;
}

template <typename T>
bool InputSlot<T>::isCompatible(const AbstractProperty * property) const
{
    if (property) {
        return static_cast<AbstractTyped *>(this)->type() == property->asTyped()->type();
    } else {
        return nullptr;
    }
}

template <typename T>
bool InputSlot<T>::connect(const AbstractProperty * property)
{
    if (!property || !isCompatible(property))
    {
        // Get source property
        m_source = static_cast< TypedProperty<T> * >(property);

        // Connect to property
        m_connection = m_source->valueChanged.connect([this] (const T & value)
        {
            this->valueChanged(value);
        } );

        // Emit events
        this->connectionChanged();
        this->changed( static_cast< Typed<T> *>(m_source->asTyped())->value() );

        return true;
    }

    return false;
}

template <typename T>
void InputSlot<T>::disconnect()
{
    // Reset source property
    m_source     = nullptr;
    m_connection = ScopedConnection();

    // Emit events
    this->connectionChanged();
    this->changed(m_defaultValue);
}

template <typename T>
AbstractTyped * InputSlot<T>::clone() const
{
    return nullptr;
}

template <typename T>
T InputSlot<T>::value() const
{
    if (m_source) {
        return static_cast< Typed<T> *>(m_source->asTyped())->value();
    } else {
        return m_defaultValue;
    }
}

template <typename T>
void InputSlot<T>::setValue(const T &)
{
    // Not supported for input slots!
}

template <typename T>
const T * InputSlot<T>::ptr() const
{
    if (m_source) {
        return static_cast< const Typed<T> *>(m_source->asTyped())->ptr();
    } else {
        return nullptr;
    }
}

template <typename T>
T * InputSlot<T>::ptr()
{
    if (m_source) {
        return static_cast< Typed<T> *>(m_source->asTyped())->ptr();
    } else {
        return nullptr;
    }
}

template <typename T>
AbstractTyped * InputSlot<T>::asTyped()
{
    return static_cast<AbstractTyped *>(this);
}

template <typename T>
const AbstractTyped * InputSlot<T>::asTyped() const
{
    return static_cast<const AbstractTyped *>(this);
}

template <typename T>
bool InputSlot<T>::isGroup() const
{
    return false;
}


} // namespace cppexpose
