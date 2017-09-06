
#pragma once


#include <cppexpose/type/AbstractTypedValue.h>


namespace cppexpose
{


/**
*  @brief
*    Typed value that is stored directly
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API InternalValue : public AbstractTypedValue<T>
{
public:
    typedef typename AbstractTypedValue<T>::BaseType    BaseType;
    typedef typename AbstractTypedValue<T>::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    InternalValue();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    InternalValue(const T & value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~InternalValue();

    // Virtual AbstractValue interface
    virtual std::unique_ptr<AbstractValue> createCopy() const override;
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

    // Virtual AbstractTypedValue<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;
    virtual const T * ptr() const override;
    virtual T * ptr() override;
    virtual size_t numElements() const override;
    virtual ElementType getElement(size_t i) const override;
    virtual void setElement(size_t i, ElementType value) override;
    virtual void push(ElementType value) override;
    virtual std::vector<std::string> keys() const override;
    virtual ElementType getElement(const std::string & key) const override;
    virtual void setElement(const std::string & key, ElementType value) override;


protected:
    T m_value; ///< Value
};


} // namespace cppexpose


#include <cppexpose/type/InternalValue.inl>
