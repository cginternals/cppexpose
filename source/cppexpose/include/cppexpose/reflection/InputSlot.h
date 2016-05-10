
#pragma once


#include <cppexpose/reflection/TypedProperty.h>
#include <cppexpose/typed/TypeSelector.h>
#include <cppexpose/signal/ScopedConnection.h>


namespace cppexpose
{


/**
*  @brief
*    Input slot that can be connected to a property
*
*  @see
*    Property
*/
template <typename T>
class InputSlot : public TypeSelector<T>::Type, public TypedProperty<T>
{
public:
    Signal<const T &> connectionChanged;  ///< Called when the connection has been changed


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] parent
    *    Parent object (must NOT be null!)
    *  @param[in] name
    *    Property name
    *
    *  @remarks
    *    The input slot is created and added to the given parent object.
    */
    InputSlot(PropertyGroup * parent, const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~InputSlot();

    /**
    *  @brief
    *    Check if input slot is compatible to data property
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    'true' if property can be connected to input slot, else 'false'
    */
    bool isCompatible(const AbstractProperty * property) const;

    /**
    *  @brief
    *    Check if input slot is connected to a data property
    *
    *  @return
    *    'true' if input slot is connected, else 'false'
    */
    bool isConnected() const;

    /**
    *  @brief
    *    Connect input slot to data property
    *
    *  @param[in] property
    *    Property
    *
    *  @return
    *    'true' if property could be connected to input slot, else 'false'
    */
    bool connect(const AbstractProperty * property);

    /**
    *  @brief
    *    Disconnect input slot
    */
    void disconnect();

    // Virtual AbstractTyped interface
    virtual AbstractTyped * clone() const override;

    // Virtual Typed<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;
    virtual const T * ptr() const override;
    virtual T * ptr() override;

    // Virtual AbstractProperty interface
    virtual AbstractTyped * asTyped() override;
    virtual const AbstractTyped * asTyped() const override;
    virtual bool isGroup() const override;


protected:
    TypedProperty<T> * m_source;       ///< Connected source (can be null)
    ScopedConnection   m_connection;   ///< Connection to changed-signal of source property
    T                  m_defaultValue; ///< Default value that is returned if unconnected
};


} // namespace cppexpose


#include <cppexpose/reflection/InputSlot.hpp>
