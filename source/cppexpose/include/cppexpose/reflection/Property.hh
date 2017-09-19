
#pragma once


#include <memory>

#include <cppexpose/signal/Signal.h>

#include <cppexpose/reflection/AbstractProperty.hh>
#include <cppexpose/value/ValueContainer.hh>


namespace cppexpose
{


/**
*  @brief
*    Typed property that holds a value
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API Property : public AbstractProperty
{
public:
    using ElementType = typename ValueContainer<T>::ElementType;


public:
    Signal<const T &> valueChanged; ///< Called when the value has been changed


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name (must NOT be empty!)
    *  @param[in] parent
    *    Parent object (can be null)
    *
    *  @remarks
    *    If parent is valid, the property is automatically added to the
    *    parent object. The ownership is not transferred, so the property
    *    has to be deleted by the caller. To transfer the ownership to the
    *    parent, call this constructor with parent(nullptr) and pass
    *    a unique_ptr to addProperty() on the parent object.
    */
    Property(const std::string & name, Object * parent = nullptr);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name (must NOT be empty!)
    *  @param[in] parent
    *    Parent object (can be null)
    *  @param[in] value
    *    Initial value
    */
    Property(const std::string & name, Object * parent, const T & value);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name (must NOT be empty!)
    *  @param[in] parent
    *    Parent object (can be null)
    *  @param[in] arguments
    *    Arguments to initialize the propery
    *
    *  @remarks
    *    Use this constructor to create a property with getter and setter methods, e.g.:
    *      Property<int> m_number("number", this, this, &MyClass::number, &MyClass::setNumber);
    */
    template <typename ... Arguments>
    Property(const std::string & name, Object * parent, Arguments && ... arguments);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Property();

    // Typed value interface
    virtual T value() const;
    virtual void setValue(const T & value);
    virtual const T * ptr() const;
    virtual T * ptr();

    // Virtual Typed interface
    virtual const Type & type() const override;
    virtual Type & type() override;
    virtual const AbstractBaseType * baseType() const override;
    virtual AbstractBaseType * baseType() override;
    virtual const Type & elementType() const override;
    virtual Type & elementType() override;
    virtual const std::string & typeName() const override;
    virtual bool isNull() const override;
    virtual bool isType() const override;
    virtual bool isConst() const override;
    virtual bool isArray() const override;
    virtual bool isDynamicArray() const override;
    virtual bool isMap() const override;
    virtual bool isBoolean() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;
    virtual bool isString() const override;

    // Virtual AbstractValueContainer interface
    virtual std::unique_ptr<AbstractValueContainer> createCopy() const override;
    virtual bool compareTypeAndValue(const AbstractValueContainer & value) const override;
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
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & variant) override;
    virtual size_t numElements() const override;
    virtual Variant element(size_t i) const override;
    virtual void setElement(size_t i, const Variant & value) override;
    virtual void pushElement(const Variant & value) override;
    virtual std::vector<std::string> keys() const override;
    virtual Variant element(const std::string & key) const override;
    virtual void setElement(const std::string & key, const Variant & value) override;

    // Virtual AbstractProperty interface
    virtual bool isObject() const override;


protected:
    std::unique_ptr<ValueContainer<T>> m_value;
};


} // namespace cppexpose
