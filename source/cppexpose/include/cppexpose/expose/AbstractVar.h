
#pragma once


#include <string>

#include <cppexpose/expose/VarType.h>


namespace cppexpose
{


class Variant;
class Object;
class Array;


/**
*  @brief
*    Abstract base class for variables
*/
class CPPEXPOSE_API AbstractVar
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractVar();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractVar();

    /**
    *  @brief
    *    Check if value has a specific type
    *
    *  @return
    *    'true' if value is of type Type, else 'false'.
    */
    template <typename Type>
    bool hasType() const;

    /**
    *  @brief
    *    Check if value type can be converted
    *
    *  @return
    *    'true' if value can be converted into type Type, else 'false'.
    *
    *  @remarks
    *    Conversion is only supported if the source type is able to convert
    *      into a basic type (number, string, or object), and the destination
    *      type is able to convert from that same basic type.
    */
    template <typename Type>
    bool canConvert() const;

    /**
    *  @brief
    *    Get value converted to type Type
    *
    *  @return
    *    Converted value (or default value for that type)
    *
    *  @remarks
    *    If the conversion fails, the value will be the default value for the given type.
    */
    template <typename Type>
    Type value() const;

    // Replication
    virtual AbstractVar * clone() const = 0;

    // Variable type
    virtual VarType type() const = 0;
    virtual bool isNull() const = 0;
    virtual bool isBool() const = 0;
    virtual bool isNumber() const = 0;
    virtual bool isIntegral() const = 0;
    virtual bool isSignedIntegral() const = 0;
    virtual bool isFloatingPoint() const = 0;
    virtual bool isEnum() const = 0;
    virtual bool isString() const = 0;
    virtual bool isExternal() const = 0;
    virtual bool isPointer() const = 0;
    virtual bool isObject() const = 0;
    virtual bool isArray() const = 0;
    virtual bool isFunction() const = 0;

    // Access modifiers
    virtual bool isConst() const = 0;

    // Additional information
    virtual Variant minimumValue() const = 0;
    virtual Variant maximumValue() const = 0;

    // Conversion to other types
    virtual bool canConvertToString() const = 0;
    virtual std::string toString() const = 0;
    virtual bool canConvertToBool() const = 0;
    virtual bool toBool() const = 0;
    virtual bool canConvertToLongLong() const = 0;
    virtual long long toLongLong() const = 0;
    virtual bool canConvertToULongLong() const = 0;
    virtual unsigned long long toULongLong() const = 0;
    virtual bool canConvertToDouble() const = 0;
    virtual double toDouble() const = 0;
    virtual bool canConvertToObject() const = 0;
    virtual Object toObject() const = 0;
    virtual bool canConvertToArray() const = 0;
    virtual Array toArray() const = 0;

    // Conversion from other types
    virtual bool canConvertFromVar(const AbstractVar & value) = 0;
    virtual void fromVar(const AbstractVar & value) = 0;
};


} // namespace cppexpose


#include <cppexpose/expose/AbstractVar.inl>
