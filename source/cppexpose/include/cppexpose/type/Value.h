
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

    // Virtual AbstractValue interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & value) override;
    virtual bool toBool() const override;
    virtual bool fromBool(bool value) override;
    virtual long long toLongLong() const override;
    virtual bool fromLongLong(long long value) override;
    virtual unsigned long long toULongLong() const override;
    virtual bool fromULongLong(unsigned long long value) override;
    virtual double toDouble() const override;
    virtual bool fromDouble(double value) override;

    // Conversions
    /*
    template <typename U>
    bool canConvert() const;

    template <typename U>
    U value() const;
    */


protected:
    T m_value; ///< Typed value
};


} // namespace cppexpose


#include <cppexpose/type/Value.inl>
