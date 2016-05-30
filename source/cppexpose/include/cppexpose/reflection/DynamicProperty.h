
#pragma once


#include <cppexpose/reflection/AbstractProperty.h>
#include <cppexpose/typed/StoredValue.h>
#include <cppexpose/signal/Signal.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of dynamic object properties
*
*    Dynamic properties are defined and added to an object
*    at runtime rather than at compile time.
*
*    Dynamic properties store the property value themselves,
*    no using getter or setter functions. Other than that,
*    they behave exactly like normal properties.
*
*  @see
*    Property
*/
template <typename T, typename BASE = AbstractProperty>
class DynamicProperty : public DirectValue<T, BASE>
{
public:
    Signal<const T &> valueChanged;  ///< Called when the value has been changed


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name (must NOT be empty!)
    *  @param[in] parent
    *    Parent object (must NOT be null!)
    *  @param[in] args
    *    Arguments for the typed value (see DirectValueSingle and DirectValueArray)
    *
    *  @remarks
    *    If parent is valid, the property is automatically added to the
    *    parent object. The parent object takes ownership over the property,
    *    so it will be destroyed together with the parent object.
    */
    template <typename... Args>
    DynamicProperty(const std::string & name, PropertyGroup * parent, Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DynamicProperty();

    // Virtual AbstractProperty interface
    virtual bool isGroup() const override;


protected:
    // Virtual Typed<T> interface
    virtual void onValueChanged(const T & value) override;
};


} // namespace cppexpose


#include <cppexpose/reflection/DynamicProperty.hpp>
