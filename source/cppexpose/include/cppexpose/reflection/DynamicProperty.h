
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/reflection/AbstractProperty.h>
#include <cppexpose/signal/Signal.h>
#include <cppexpose/typed/DirectValue.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of dynamic object properties
*
*    Dynamic properties are defined and added to an object
*    at runtime rather than at compile time. In contrast to
*    normal properties, they store the property value themselves
*    instead of using getter or setter functions. Other than
*    that, they behave exactly like normal properties.
*
*  @see
*    Property
*/
template <typename T, typename BASE = AbstractProperty>
class CPPEXPOSE_TEMPLATE_API DynamicProperty : public DirectValue<T, BASE>
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
    *    Arguments for the typed value (see DirectValueSingle and DirectValueArray)
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
    DynamicProperty(const std::string & name, Object * parent, Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DynamicProperty();

    // Virtual AbstractProperty interface
    virtual bool isObject() const override;


protected:
    // Virtual Typed<T> interface
    virtual void onValueChanged(const T & value) override;
};


} // namespace cppexpose


#include <cppexpose/reflection/DynamicProperty.inl>
