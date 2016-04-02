
#pragma once


#include <cppexpose/typed/TypeSelector.h>


namespace cppexpose
{


/**
*  @brief
*    Typed array value (read/write) that is stored directly
*/
template <typename T>
class DirectArrayValue : public TypeSelector<T>::Type
{
public:
    typedef typename TypeSelector<T>::Type::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    DirectArrayValue();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DirectArrayValue();

    // Virtual Typed<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;

    // Virtual TypedArray<T> interface
    virtual ElementType getElement(size_t i) const override;
    virtual void setElement(size_t i, const ElementType & value) override;


protected:
    T m_value;  ///< The stored value
};


/**
*  @brief
*    Typed array value (read-only) that is stored directly
*/
template <typename T>
class DirectArrayValue<const T> : public DirectArrayValue<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    DirectArrayValue();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DirectArrayValue();

    // Virtual AbstractTyped interface
    virtual bool isReadOnly() const override;

    // Virtual Typed<T> interface
    virtual void setValue(const T & value) override;

    // Virtual TypedArray<T> interface
    virtual void setElement(size_t i, const typename DirectArrayValue<T>::ElementType & value) override;
};


} // namespace cppexpose


#include <cppexpose/typed/DirectArrayValue.hpp>
