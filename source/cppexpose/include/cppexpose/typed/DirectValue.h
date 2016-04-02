
#pragma once


#include <cppexpose/typed/TypeSelector.h>


namespace cppexpose
{


/**
*  @brief
*    Typed value (read/write) that is stored directly
*/
template <typename T>
class DirectValue : public TypeSelector<T>::Type
{
public:
    /**
    *  @brief
    *    Constructor
    */
    DirectValue();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DirectValue();

    // Virtual Typed<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;


protected:
    T m_value;  ///< The stored value
};


/**
*  @brief
*    Typed value (read-only) that is stored directly
*/
template <typename T>
class DirectValue<const T> : public DirectValue<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    DirectValue();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DirectValue();

    // Virtual AbstractTyped interface
    virtual bool isReadOnly() const override;

    // Virtual Typed<T> interface
    virtual void setValue(const T & value) override;
};


} // namespace cppexpose


#include <cppexpose/typed/DirectValue.hpp>
