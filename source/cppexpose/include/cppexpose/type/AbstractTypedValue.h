
#pragma once


#include <cppexpose/signal/Signal.h>
#include <cppexpose/type/AbstractValue.h>
#include <cppexpose/type/Type.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class for typed values
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API AbstractTypedValue : public AbstractValue
{
public:
    typedef typename Type<T>::BaseType    BaseType;
    typedef typename Type<T>::ElementType ElementType;


public:
    Signal<const T &> valueChanged;  ///< Called when the value has been changed


public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractTypedValue();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractTypedValue();

    // Value access
    virtual T value() const = 0;
    virtual void setValue(const T & value) = 0;
    virtual const T * ptr() const = 0;
    virtual T * ptr() = 0;

    // Array interface
    virtual size_t numElements() const = 0;
    virtual ElementType getElement(size_t i) const = 0;
    virtual void setElement(size_t i, ElementType value) = 0;
    virtual void push(ElementType value) = 0;

    // Virtual AbstractValue interface
    virtual const AbstractType & type() const override;

    // Virtual IType interface
    virtual const std::type_info & typeInfo() const override;
    virtual std::string typeName() const override;
    virtual bool isConst() const override;
    virtual bool isArray() const override;
    virtual bool isDynamicArray() const override;
    virtual bool isBoolean() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;
    virtual bool isString() const override;


protected:
    Type<T> m_type;  ///< Object that described the type of the value
};


} // namespace cppexpose


#include <cppexpose/type/AbstractTypedValue.inl>
