
#pragma once


#include <cppexpose/expose/AbstractVar.h>
#include <cppexpose/expose/ValueStorage.h>
#include <cppexpose/expose/Var.h> // Important for template reasons
#include <cppexpose/expose/GetTyped.h>


namespace cppexpose
{


class PropertyContainer;


/**
*  @brief
*    Typed property on an object or array
*
*    A property describes a typed value that belongs to an object or array.
*    It defines a value type and provides an interface through which
*    this value can be accessed at runtime. For example, the type
*    and value can be queried, and automatic type conversions can be
*    invoked. Properties are for example used to expose object values
*    for UI or scripting interfaces.
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API Property : public GetTyped< Type, ValueStorage<Type, AbstractVar> >::VarType
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    Property(const Type & value);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    Property(const Type & value, Args&&... args);

    /**
    *  @brief
    *    Constructor that registers the property at a parent container
    *
    *  @param[in] name
    *    Name of property
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    */
    Property(const std::string & name, PropertyContainer * parent);

    /**
    *  @brief
    *    Constructor that registers the property at a parent container
    *
    *  @param[in] name
    *    Name of property
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    *  @param[in] value
    *    Initial value
    */
    Property(const std::string & name, PropertyContainer * parent, const Type & value);

    /**
    *  @brief
    *    Constructor that registers the property at a parent container
    *
    *  @param[in] name
    *    Name of property
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    *  @param[in] value
    *    Initial value
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    Property(const std::string & name, PropertyContainer * parent, const Type & value, Args&&... args);

    /**
    *  @brief
    *    Copy Constructor
    *
    *  @param[in] prop
    *    Property that is copied
    *
    *  @remarks
    *    This copies only the value of the property.
    *    Name and parent are set to their default values.
    */
    Property(const Property<Type> & prop);

    /**
    *  @brief
    *    Constructor that copies from another var
    *
    *  @param[in] var
    *    Var that is copied
    */
    Property(const AbstractVar & var);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Property();

    /**
    *  @brief
    *    Assignment operator
    *
    *  @param[in] var
    *    Variable whose value is copied
    */
    Property<Type> & operator =(const AbstractVar & var);

    // Replication
    virtual std::unique_ptr<AbstractVar> move() override;
};


} // namespace cppexpose


#include <cppexpose/expose/Property.inl>
