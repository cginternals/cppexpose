
#pragma once


#include <cppexpose/type/AbstractTypedValue.h>


namespace cppexpose
{


/**
*  @brief
*    Typed value
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API Value : public AbstractTypedValue<T>
{
public:
    typedef typename AbstractTypedValue<T>::BaseType    BaseType;
    typedef typename AbstractTypedValue<T>::ElementType ElementType;


public:
    Value();
    virtual ~Value();

    // Virtual AbstractTypedValue<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;
    virtual const T * ptr() const override;
    virtual T * ptr() override;

    virtual size_t numElements() const override;
    virtual ElementType getElement(size_t i) const override;
    virtual void setElement(size_t i, ElementType value) override;
    virtual void push(ElementType value) override;


protected:
    T m_value; ///< Typed value
};


} // namespace cppexpose


#include <cppexpose/type/Value.inl>
