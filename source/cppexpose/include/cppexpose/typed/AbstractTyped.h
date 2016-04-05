
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class Variant;


/**
*  @brief
*    Base interface for typed values
*/
class CPPEXPOSE_API AbstractTyped
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
    *    Check if value is of enum-type
    *
    *  @return
    *    'true' if value is an enum, else 'false'
    */
    virtual bool isEnum() const = 0;

    /**
    *  @brief
    *    Check if value is of array-type
    *
    *  @return
    *    'true' if value is an array, else 'false'
    */
    virtual bool isArray() const = 0;

    /**
    *  @brief
    *    Check if value is of type cppexpose::Variant
    *
    *  @return
    *    'true' if value is a variant, else 'false'
    */
    virtual bool isVariant() const = 0;

    /**
    *  @brief
    *    Check if value is of type string
    *
    *  @return
    *    'true' if value is a string, else 'false'
    */
    virtual bool isString() const = 0;

    /**
    *  @brief
    *    Check if value is of type bool
    *
    *  @return
    *    'true' if value is a bool, else 'false'
    */
    virtual bool isBool() const = 0;

    /**
    *  @brief
    *    Check if value is a number
    *
    *  @return
    *    'true' if value is a number, else 'false'
    */
    virtual bool isNumber() const = 0;

    /**
    *  @brief
    *    Check if value is an integral
    *
    *  @return
    *    'true' if value is a integral, else 'false'
    */
    virtual bool isIntegral() const = 0;

    /**
    *  @brief
    *    Check if value is a signed integral
    *
    *  @return
    *    'true' if value is a signed integral, else 'false'
    */
    virtual bool isSignedIntegral() const = 0;

    /**
    *  @brief
    *    Check if value is an unsigned integral
    *
    *  @return
    *    'true' if value is an unsigned integral, else 'false'
    */
    virtual bool isUnsignedIntegral() const = 0;

    /**
    *  @brief
    *    Check if value is a floating point number
    *
    *  @return
    *    'true' if value is a floating point number, else 'false'
    */
    virtual bool isFloatingPoint() const = 0;

    /**
    *  @brief
    *    Convert value into variant
    *
    *  @return
    *    Variant representation of the value
    */
    virtual Variant toVariant() const = 0;

    /**
    *  @brief
    *    Set value from variant
    *
    *  @param[in] value
    *    Variant value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromVariant(const Variant & value) = 0;

    /**
    *  @brief
    *    Convert value into string
    *
    *  @return
    *    String representation of the value
    */
    virtual std::string toString() const = 0;

    /**
    *  @brief
    *    Set value from string
    *
    *  @param[in] value
    *    String value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromString(const std::string & value) = 0;

    /**
    *  @brief
    *    Convert value into bool
    *
    *  @return
    *    Converted value
    */
    virtual bool toBool() const = 0;

    /**
    *  @brief
    *    Set value from bool
    *
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromBool(bool value) = 0;

    /**
    *  @brief
    *    Convert value into long long
    *
    *  @return
    *    Converted value
    */
    virtual long long toLongLong() const = 0;

    /**
    *  @brief
    *    Set value from long long
    *
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromLongLong(long long value) = 0;

    /**
    *  @brief
    *    Convert value into unsigned long long
    *
    *  @return
    *    Converted value
    */
    virtual unsigned long long toULongLong() const = 0;

    /**
    *  @brief
    *    Set value from unsigned long long
    *
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromULongLong(unsigned long long value) = 0;

    /**
    *  @brief
    *    Convert value into double
    *
    *  @return
    *    Converted value
    */
    virtual double toDouble() const = 0;

    /**
    *  @brief
    *    Set value from double
    *
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromDouble(double value) = 0;

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
    template <typename ValueType>
    ValueType convert(const ValueType & defaultValue = ValueType()) const;
};


} // namespace cppexpose


#include <cppexpose/typed/AbstractTyped.hpp>
