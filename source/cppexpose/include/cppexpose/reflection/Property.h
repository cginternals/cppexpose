
#pragma once


#include <cppexpose/reflection/AbstractProperty.h>
#include <cppexpose/typed/StoredValue.h>
#include <cppexpose/signal/Signal.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of object properties
*
*    A property describes a variable value that belongs to an object.
*    It defines name and value type and provides an interface through
*    which this value can be accessed at runtime. For example, the type
*    and value can be queried, and automatic type conversions can be
*    invoked. Properties are for example used to expose object values
*    for UI and scripting interfaces.
*
*    Regular properties defined by this class use getter and setter
*    methods to access the actual property value. Those are specified
*    when declaring the property. This kind of property is regarded
*    as static, since the property is defined on a class and is always
*    present when an object of that class is created. For creating
*    properties on objects dynamically at runtime, see DynamicProperty.
*/
template <typename T, typename BASE = AbstractProperty>
class Property : public StoredValue<T, BASE>
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
    *    Parent object (can be null)
    *  @param[in] args
    *    Arguments for the typed value (see StoredValueSingle and StoredValueArray)
    *
    *  @remarks
    *    If parent is valid, the property is automatically added to the
    *    parent object. The ownership is not transferred, so the property
    *    has to be deleted by the caller.
    *
    *    To transfer the ownership to the parent, call this constructor with
    *    parent(nullptr), and use addProperty() on the parent object.
    */
    template <typename... Args>
    Property(const std::string & name, Object * parent, Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Property();

    // Virtual AbstractProperty interface
    virtual bool isObject() const override;


protected:
    // Virtual Typed<T> interface
    virtual void onValueChanged(const T & value) override;
};


} // namespace cppexpose


#include <cppexpose/reflection/Property.inl>
