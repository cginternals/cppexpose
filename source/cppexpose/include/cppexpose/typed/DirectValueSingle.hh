
#pragma once


#include <cppexpose/typed/GetTyped.hh>


namespace cppexpose
{


/**
*  @brief
*    Typed value (read/write) that is stored directly
*/
template <typename T, typename BASE>
class DirectValueSingle : public GetTyped<T, BASE>::Type
{
public:
    /**
    *  @brief
    *    Constructor
    */
    DirectValueSingle();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    DirectValueSingle(const T & value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DirectValueSingle();

    // Virtual AbstractTyped interface
    virtual AbstractTyped * clone() const override;

    // Virtual Typed<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;
    virtual const T * ptr() const override;
    virtual T * ptr() override;


protected:
    T m_value;  ///< The stored value
};


/**
*  @brief
*    Typed value (read-only) that is stored directly
*/
template <typename T, typename BASE>
class DirectValueSingle<const T, BASE> : public DirectValueSingle<T, BASE>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    DirectValueSingle();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    DirectValueSingle(const T & value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DirectValueSingle();

    // Virtual AbstractTyped interface
    virtual AbstractTyped * clone() const override;
    virtual bool isReadOnly() const override;

    // Virtual Typed<T> interface
    virtual void setValue(const T & value) override;
    virtual T * ptr() override;
};


} // namespace cppexpose
