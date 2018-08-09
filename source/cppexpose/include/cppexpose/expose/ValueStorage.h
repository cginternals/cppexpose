
#pragma once


#include <cppexpose/expose/AbstractTyped.h>


namespace cppexpose
{


template <typename Type>
class Var;


/**
*  @brief
*    Direct variable storage (non-const type)
*/
template <typename Type, typename BaseClass>
class CPPEXPOSE_TEMPLATE_API ValueStorage : public AbstractTyped<Type, BaseClass>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ValueStorage();

    /**
    *  @brief
    *    Constructor that copies from another var
    *
    *  @param[in] var
    *    Var that is copied
    */
    ValueStorage(const AbstractVar & var);

    /**
    *  @brief
    *    Constructor that copies from another var
    *
    *  @param[in] defaultValue
    *    Initial value (ignored in this case)
    *  @param[in] var
    *    Var that is copied
    */
    ValueStorage(const Type & defaultValue, const AbstractVar & var);

    /**
    *  @brief
    *    Constructor with initial value
    *
    *  @param[in] defaultValue
    *    Initial value (ignored in this case)
    *  @param[in] value
    *    Initial value
    */
    ValueStorage(const Type & defaultValue, const Type & value);

    /**
    *  @brief
    *    Constructor with default value
    *
    *  @param[in] defaultValue
    *    Default value
    */
    ValueStorage(const Type & defaultValue);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ValueStorage();

    // Replication
    virtual AbstractVar * clone() const override;

    // Variable type
    //   Overloaded in derived classes

    // Access modifiers
    virtual bool isConst() const override;

    // Value access
    virtual const Type & value() const override;
    virtual void setValue(const Type & value) override;

protected:
    Type m_value; ///< The actual value of the variable
};


/**
*  @brief
*    Direct variable storage (const type)
*/
template <typename Type, typename BaseClass>
class CPPEXPOSE_TEMPLATE_API ValueStorage<const Type, BaseClass> : public AbstractTyped<Type, BaseClass>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ValueStorage();

    /**
    *  @brief
    *    Constructor that copies from another var
    *
    *  @param[in] var
    *    Var that is copied
    */
    ValueStorage(const AbstractVar & var);

    /**
    *  @brief
    *    Constructor that copies from another var
    *
    *  @param[in] defaultValue
    *    Initial value (ignored in this case)
    *  @param[in] var
    *    Var that is copied
    */
    ValueStorage(const Type & defaultValue, const AbstractVar & var);

    /**
    *  @brief
    *    Constructor with initial value
    *
    *  @param[in] defaultValue
    *    Initial value (ignored in this case)
    *  @param[in] value
    *    Initial value
    */
    ValueStorage(const Type & defaultValue, const Type & value);

    /**
    *  @brief
    *    Constructor with default value
    *
    *  @param[in] defaultValue
    *    Default value
    */
    ValueStorage(const Type & defaultValue);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ValueStorage();

    // Replication
    virtual AbstractVar * clone() const override;

    // Variable type
    //   Overloaded in derived classes

    // Access modifiers
    virtual bool isConst() const override;

    // Value access
    virtual const Type & value() const override;
    virtual void setValue(const Type & value) override;

protected:
    Type m_value; ///< The actual value of the variable
};


} // namespace cppexpose


#include <cppexpose/expose/ValueStorage.inl>
