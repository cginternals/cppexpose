
#pragma once


#include <string>

#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


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
};


} // namespace cppexpose
