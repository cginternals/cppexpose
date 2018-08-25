
#pragma once


#include <cppexpose/ValueStorage.h>
#include <cppexpose/GetTyped.h>


namespace cppexpose
{


/**
*  @brief
*    Typed variable
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API Var : public GetTyped<Type>::VarType
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
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    *  @param[in] name
    *    Name of property
    */
    Var(PropertyContainer * parent, const std::string & name);

    /**
    *  @brief
    *    Constructor that registers the property, and initial value
    *
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    *  @param[in] name
    *    Name of property
    *  @param[in] value
    *    Initial value
    */
    Var(PropertyContainer * parent, const std::string & name, const Type & value);

    /**
    *  @brief
    *    Constructor that registers the property, initial value and additional arguments
    *
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    *  @param[in] name
    *    Name of property
    *  @param[in] value
    *    Initial value
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    Var(PropertyContainer * parent, const std::string & name, const Type & value, Args&&... args);

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
    Var<Type> & operator =(const Var<Type> & var);

    /**
    *  @brief
    *    Assignment operator
    *
    *  @param[in] var
    *    Variable whose value is copied
    */
    Var<Type> & operator =(const AbstractVar & var);

    /**
    *  @brief
    *    Assignment operator
    *
    *  @param[in] value
    *    New value
    */
    Var<Type> & operator =(const Type & value);

    // Replication
    virtual std::unique_ptr<AbstractVar> move() override;
};


} // namespace cppexpose


#include <cppexpose/Var.inl>
