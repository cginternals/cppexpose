
#pragma once


#include <cppexpose/reflection/TypedProperty.h>
#include <cppexpose/typed/StoredValue.hh>


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
template <typename T>
class DynamicProperty : public DirectValue<T>, public TypedProperty<T>
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
    *    Arguments for the typed value (see DirectValueSingle and DirectValueArray)
    *
    *  @remarks
    *    The property is created and added to the given parent object.
    *    The parent object takes ownership over the property, so it
    *    will be destroyed together with the parent object.
    */
    template <typename... Args>
    DynamicProperty(PropertyGroup * parent, const std::string & name, Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DynamicProperty();

    // Virtual AbstractProperty interface
    virtual AbstractTyped * asTyped() override;
    virtual const AbstractTyped * asTyped() const override;


protected:
    // Virtual Typed<T> interface
    virtual void onValueChanged(const T & value) override;
};


} // namespace cppexpose


#include <cppexpose/reflection/DynamicProperty.hpp>
