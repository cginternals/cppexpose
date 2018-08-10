
#pragma once


#include <cppexpose/expose/ValueStorage.h>
#include <cppexpose/expose/GetTyped.h>


namespace cppexpose
{


/**
*  @brief
*    Typed variable
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API Var : public GetTyped< Type, ValueStorage<Type> >::VarType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Var();

    /**
    *  @brief
    *    Constructor with initial value
    *
    *  @param[in] value
    *    Initial value
    */
    Var(const Type & defaultValue);

    /**
    *  @brief
    *    Constructor with initial value and additional arguments
    *
    *  @param[in] value
    *    Initial value
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    Var(const Type & defaultValue, Args&&... args);

    /**
    *  @brief
    *    Constructor that registers the property at a parent container
    *
    *  @param[in] name
    *    Name of property
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    */
    Var(const std::string & name, PropertyContainer * parent);

    /**
    *  @brief
    *    Constructor that registers the property, and initial value
    *
    *  @param[in] name
    *    Name of property
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    *  @param[in] value
    *    Initial value
    */
    Var(const std::string & name, PropertyContainer * parent, const Type & value);

    /**
    *  @brief
    *    Constructor that registers the property, initial value and additional arguments
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
    Var(const std::string & name, PropertyContainer * parent, const Type & value, Args&&... args);

    /**
    *  @brief
    *    Copy Constructor
    *
    *  @param[in] var
    *    Var that is copied
    */
    Var(const Var<Type> & var);

    /**
    *  @brief
    *    Constructor that copies the value from another var
    *
    *  @param[in] var
    *    Var that is copied
    */
    Var(const AbstractVar & var);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Var();

    /**
    *  @brief
    *    Assignment operator
    *
    *  @param[in] var
    *    Variable whose value is copied
    */
    Var<Type> & operator =(const AbstractVar & var);

    // Replication
    virtual std::unique_ptr<AbstractVar> move() override;
};


} // namespace cppexpose


#include <cppexpose/expose/Var.inl>
