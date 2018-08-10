
#pragma once


#include <cppexpose/expose/AbstractVar.h>
#include <cppexpose/expose/ValueStorage.h>
#include <cppexpose/expose/GetTyped.h>


namespace cppexpose
{


/**
*  @brief
*    Typed variable
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API Var : public GetTyped< Type, ValueStorage<Type, AbstractVar> >::VarType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Var();

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
    *    Constructor that copies from another var
    *
    *  @param[in] var
    *    Var that is copied
    */
    Var(const AbstractVar & var);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] defaultValue
    *    Default value (used if no initial value is given in args)
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    Var(const Type & defaultValue, Args&&... args);

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
