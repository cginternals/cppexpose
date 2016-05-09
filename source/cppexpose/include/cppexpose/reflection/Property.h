
#pragma once


#include <cppexpose/reflection/TypedProperty.h>
#include <cppexpose/typed/StoredValue.hh>


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
template <typename T>
class Property : public StoredValue<T>, public TypedProperty<T>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] parent
    *    Parent object (must NOT be null!)
    *  @param[in] name
    *    Property name
    *  @param[in] args
    *    Arguments for the typed value (see StoredValueSingle and StoredValueArray)
    *
    *  @remarks
    *    The property is created and added to the given parent object.
    */
    template <typename... Args>
    Property(PropertyGroup * parent, const std::string & name, Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Property();

    // Virtual AbstractProperty interface
    virtual AbstractTyped * asTyped() override;
    virtual const AbstractTyped * asTyped() const override;


protected:
    // Virtual Typed<T> interface
    virtual void onValueChanged(const T & value) override;
};


} // namespace cppexpose


#include <cppexpose/reflection/Property.hpp>
