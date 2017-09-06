
#pragma once


#include <cppexpose/type/AbstractTypedType.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of an enum type
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API TypeEnum : public AbstractTypedType<T, T>
{
public:
    typedef T BaseType;
    typedef T ElementType;
    typedef typename std::underlying_type<T>::type UnderlyingType;


public:
    /**
    *  @brief
    *    Constructor
    */
    TypeEnum();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypeEnum();

    // Virtual AbstractType interface
    virtual std::string typeName() const override;
    virtual bool isNull() const override;
    virtual bool isArray() const override;
    virtual bool isDynamicArray() const override;
    virtual bool isMap() const override;
    virtual bool isBoolean() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;
    virtual bool isString() const override;
    virtual bool isType() const override;

    // Virtual AbstractTypedType<T, T> interface
    virtual const T & defaultValue() const override;

    virtual std::string toString(const T & var) const override;
    virtual bool fromString(T & var, const std::string & value) const override;
    virtual bool toBool(const T & var) const override;
    virtual bool fromBool(T & var, bool value) const override;
    virtual long long toLongLong(const T & var) const override;
    virtual bool fromLongLong(T & var, long long value) const override;
    virtual unsigned long long toULongLong(const T & var) const override;
    virtual bool fromULongLong(T & var, unsigned long long value) const override;
    virtual double toDouble(const T & var) const override;
    virtual bool fromDouble(T & var, double value) const override;
    virtual size_t numElements(const T & var) const override;
    virtual T getElement(const T & var, size_t i) const override;
    virtual void setElement(T & var, size_t i, T value) const override;
    virtual void push(T & var, T value) const override;
    virtual std::vector<std::string> keys(const T & var) const override;
    virtual T getElement(const T & var, const std::string & key) const override;
    virtual void setElement(T & var, const std::string & key, T value) const override;
};


} // namespace cppexpose


#include <cppexpose/type/TypeEnum.inl>
