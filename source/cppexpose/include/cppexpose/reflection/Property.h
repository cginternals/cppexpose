
#pragma once


#include <cppexpose/typed/StoredValue.h>
#include <cppexpose/reflection/AbstractProperty.h>


namespace cppexpose
{


/**
*  @brief
*    Representation for typed properties of an object
*/
template <typename T>
class CPPEXPOSE_API Property : public Typed<T>, public AbstractProperty
{
public:
    // [TODO]
    // Signal<const T &> valueChanged;  ///< Called when the value has been changed


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name
    *  @param[in] args
    *    Arguments for the typed value (see StoredValueSingle and StoredValueArray)
    */
    template <typename... Args>
    Property(const std::string & name, Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Property();

    // Virtual AbstractProperty interface
    virtual AbstractTyped * asTyped() override;
    virtual const AbstractTyped * asTyped() const override;
    virtual bool isGroup() const override;

    // Virtual Typed<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;

    // Virtual AbstractTyped interface
    virtual AbstractTyped * clone() const;
    virtual const std::type_info & type() const;
    virtual std::string typeName() const;
    virtual bool isReadOnly() const;
    virtual bool isComposite() const;
    virtual size_t numSubValues() const;
    virtual AbstractTyped * subValue(size_t i);
    virtual bool isEnum() const override;
    virtual bool isArray() const override;
    virtual bool isVariant() const override;
    virtual bool isString() const override;
    virtual bool isBool() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isSignedIntegral() const override;
    virtual bool isUnsignedIntegral() const override;
    virtual bool isFloatingPoint() const override;
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;
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


protected:
    virtual void onValueChanged(const T & value) override;


protected:
    StoredValue<T> * m_value;
};


} // namespace cppexpose


#include <cppexpose/reflection/Property.hpp>
