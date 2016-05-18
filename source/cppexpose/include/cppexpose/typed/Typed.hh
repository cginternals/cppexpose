
#pragma once


#include <cppexpose/typed/AbstractTyped.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a typed value
*/
template <typename T, typename BASE>
class Typed : public BASE
{
public:
    typedef T Type;  ///< Type of the value


public:
    /**
    *  @brief
    *    Constructor
    */
    Typed();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Typed();

    /**
    *  @brief
    *    Get value
    *
    *  @return
    *    Value
    */
    virtual T value() const = 0;

    /**
    *  @brief
    *    Set value
    *
    *  @param[in] value
    *    Value
    */
    virtual void setValue(const T & value) = 0;

    /**
    *  @brief
    *    Get pointer to value
    *
    *  @return
    *    Pointer to value (can be null)
    *
    *  @remarks
    *    Whether or not a pointer to the value can be returned
    *    depends on the actual storage type. So be aware that
    *    is function can return nullptr if it is called for example
    *    on a StoredValue.
    */
    virtual const T * ptr() const = 0;

    /**
    *  @brief
    *    Get pointer to value
    *
    *  @return
    *    Pointer to value (can be null)
    *
    *  @remarks
    *    Whether or not a pointer to the value can be returned
    *    depends on the actual storage type. So be aware that
    *    is function can return nullptr if it is called for example
    *    on a StoredValue.
    */
    virtual T * ptr() = 0;

    // Virtual AbstractTyped interface
    virtual const std::type_info & type() const override;
    virtual bool isReadOnly() const override;

    virtual bool isComposite() const override;
    virtual size_t numSubValues() const override;
    virtual AbstractTyped * subValue(size_t i) override;

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
    virtual void onValueChanged(const T & value);
};


} // namespace cppexpose
