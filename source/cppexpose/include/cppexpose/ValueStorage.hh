
#pragma once


#include <cppexpose/ValueStorage.hh>


namespace cppexpose
{


template <typename Type>
class Var;


/**
*  @brief
*    Value storage for a typed variable (non-const type)
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API ValueStorage : public AbstractTyped<Type>
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

    // Casting
    virtual const AbstractVar * innermost() const override;
    virtual AbstractVar * innermost() override;

    // Replication
    virtual std::unique_ptr<AbstractVar> clone() const override;

    // Variable type
    //   Overloaded in derived classes

    // Access modifiers
    virtual bool isConst() const override;

    // Value access
    virtual const Type & value() const override;
    virtual void setValue(const Type & value) override;
    virtual const Type * get() const override;
    virtual Type * get() override;

protected:
    Type m_value; ///< The actual value of the variable
};


/**
*  @brief
*    Value storage for a typed variable (const type)
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API ValueStorage<const Type> : public AbstractTyped<Type>
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

    // Casting
    virtual const AbstractVar * innermost() const override;
    virtual AbstractVar * innermost() override;

    // Replication
    virtual std::unique_ptr<AbstractVar> clone() const override;

    // Variable type
    //   Overloaded in derived classes

    // Access modifiers
    virtual bool isConst() const override;

    // Value access
    virtual const Type & value() const override;
    virtual void setValue(const Type & value) override;
    virtual const Type * get() const override;
    virtual Type * get() override;

protected:
    Type m_value; ///< The actual value of the variable
};


} // namespace cppexpose
