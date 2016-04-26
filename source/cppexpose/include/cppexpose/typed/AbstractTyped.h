
#pragma once


#include <string>

#include <cppexpose/typed/TypeInterface.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class for typed values
*/
class CPPEXPOSE_API AbstractTyped : public TypeInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractTyped();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractTyped();

    /**
    *  @brief
    *    Create a copy of the typed value
    *
    *  @return
    *    Pointer to the cloned value
    */
    virtual AbstractTyped * clone() const = 0;

    /**
    *  @brief
    *    Get type
    *
    *  @return
    *    Type id
    */
    virtual const std::type_info & type() const = 0;

    /**
    *  @brief
    *    Get human-readable type name
    *
    *  @return
    *    Type name
    */
    virtual std::string typeName() const = 0;

    /**
    *  @brief
    *    Check if value is const (read-only)
    *
    *  @return
    *    'true' if value is read-only, else 'false'
    */
    virtual bool isReadOnly() const = 0;

    /**
    *  @brief
    *    Check if value is a composite type (contains sub-values)
    *
    *  @return
    *    'true' if value is composite, else 'false'
    */
    virtual bool isComposite() const = 0;

    /**
    *  @brief
    *    Get number of sub-values
    *
    *  @return
    *    Number of sub-values, 0 if not a composite
    */
    virtual size_t numSubValues() const = 0;

    /**
    *  @brief
    *    Get sub-value as typed value
    *
    *  @param[in] i
    *    Index of sub-value
    *
    *  @return
    *    Pointer to typed sub-value, nullptr on error
    */
    virtual AbstractTyped * subValue(size_t i) = 0;

    /**
    *  @brief
    *    Check if variant type can be converted
    *
    *  @return
    *    'true' if variant can be converted into type ValueType, else 'false'.
    *
    *  @remarks
    *    Conversion is only supported for the following primitive data types:
    *      bool, char, unsigned char, short, unsigned short, int, unsigned int,
    *      long, unsigned long, long long, unsigned long long, float, double,
    *      std::string
    */
    template <typename ValueType>
    bool canConvert() const;

    /**
    *  @brief
    *    Get stored value
    *
    *  @param[in] defaultValue
    *    Default value that is returned if the value cannot be returned or converted
    *
    *  @return
    *    Stored value of type ValueType, or defaultValue if type does not match and cannot be converted
    */
    template <typename T>
    T convert(const T & defaultValue = T()) const;

    // Virtual TypeInterface interface
    virtual bool isEnum() const override = 0;
    virtual bool isArray() const override = 0;
    virtual bool isVariant() const override = 0;
    virtual bool isString() const override = 0;
    virtual bool isBool() const override = 0;
    virtual bool isNumber() const override = 0;
    virtual bool isIntegral() const override = 0;
    virtual bool isSignedIntegral() const override = 0;
    virtual bool isUnsignedIntegral() const override = 0;
    virtual bool isFloatingPoint() const override = 0;
    virtual Variant toVariant() const override = 0;
    virtual bool fromVariant(const Variant & value) override = 0;
    virtual std::string toString() const override = 0;
    virtual bool fromString(const std::string & value) override = 0;
    virtual bool toBool() const override = 0;
    virtual bool fromBool(bool value) override = 0;
    virtual long long toLongLong() const override = 0;
    virtual bool fromLongLong(long long value) override = 0;
    virtual unsigned long long toULongLong() const override = 0;
    virtual bool fromULongLong(unsigned long long value) override = 0;
    virtual double toDouble() const override = 0;
    virtual bool fromDouble(double value) override = 0;
};


} // namespace cppexpose


#include <cppexpose/typed/AbstractTyped.hpp>
