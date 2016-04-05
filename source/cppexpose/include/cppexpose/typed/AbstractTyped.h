
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

    virtual bool isComposite() const = 0;
    virtual size_t numSubValues() const = 0;
    virtual AbstractTyped * subValue(size_t i) = 0;

    virtual bool isEnum() const = 0;
    virtual bool isArray() const = 0;
    virtual bool isVariant() const = 0;
    virtual bool isString() const = 0;
    virtual bool isBool() const = 0;
    virtual bool isNumber() const = 0;
    virtual bool isIntegral() const = 0;
    virtual bool isSignedIntegral() const = 0;
    virtual bool isUnsignedIntegral() const = 0;
    virtual bool isFloatingPoint() const = 0;

    virtual Variant toVariant() const = 0;
    virtual bool fromVariant(const Variant & value) = 0;
    virtual std::string toString() const = 0;
    virtual bool fromString(const std::string & value) = 0;
    virtual bool toBool() const = 0;
    virtual bool fromBool(bool value) = 0;
    virtual long long toLongLong() const = 0;
    virtual bool fromLongLong(long long value) = 0;
    virtual unsigned long long toULongLong() const = 0;
    virtual bool fromULongLong(unsigned long long value) = 0;
    virtual double toDouble() const = 0;
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
