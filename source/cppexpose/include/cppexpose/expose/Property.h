
#pragma once


#include <cppexpose/expose/AbstractProperty.h>
#include <cppexpose/expose/ValueStorage.h>
#include <cppexpose/expose/GetTyped.h>


namespace cppexpose
{


class PropertyContainer;


/**
*  @brief
*    Typed property on an object or array
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API Property : public GetTyped< Type, ValueStorage<Type, AbstractProperty> >::VarType
{
public:
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
    *    Constructor
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
    *    Constructor
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
    *    Constructor
    *
    *  @param[in] name
    *    Name of property
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    */
    Property(const std::string & name, PropertyContainer * parent);

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
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    Property(const Type & value);

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
};


} // namespace cppexpose


#include <cppexpose/expose/Property.inl>
