
#pragma once


#include <string>
#include <vector>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractBaseType;
class Type;
template <typename T>
class BaseType;


/**
*  @brief
*    Base interface for accessing types and typed values
*
*    This interface allows for accessing and querying information about
*    data types. It is used for both types and typed values.
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
    *    Check type
    *
    *  @return
    *    'true' if type equals ValueType, else 'false'
    */
    template <typename ValueType>
    bool hasType() const;

    /**
    *  @brief
    *    Get type
    *
    *  @return
    *    Type object
    */
    virtual const Type & type() const = 0;

    /**
    *  @brief
    *    Get type
    *
    *  @return
    *    Type object
    */
    virtual Type & type() = 0;

    /**
    *  @brief
    *    Get base type
    *
    *  @return
    *    Type object
    */
    virtual const AbstractBaseType * baseType() const = 0;

    /**
    *  @brief
    *    Get base type
    *
    *  @return
    *    Type object
    */
    virtual AbstractBaseType * baseType() = 0;

    /**
    *  @brief
    *    Get type of elements
    *
    *  @return
    *    Type object
    *
    *  @remarks
    *    For container types, this returns the type of the items of the container.
    *    For all other types, the original type is returned.
    */
    virtual const Type & elementType() const = 0;

    /**
    *  @brief
    *    Get type of elements
    *
    *  @return
    *    Type object
    *
    *  @remarks
    *    For container types, this returns the type of the items of the container.
    *    For all other types, the original type is returned.
    */
    virtual Type & elementType() = 0;

    /**
    *  @brief
    *    Get type name
    *
    *  @return
    *    Type name
    */
    virtual const std::string & typeName() const = 0;

    /**
    *  @brief
    *    Check if type is empty
    *
    *  @return
    *    'true' if type is empty, else 'false'
    */
    virtual bool isNull() const = 0;

    /**
    *  @brief
    *    Check if type is a type
    *
    *  @return
    *    'true' if type is a type, else 'false'
    */
    virtual bool isType() const = 0;

    /**
    *  @brief
    *    Check if type is const (read-only)
    *
    *  @return
    *    'true' if type is const, else 'false'
    */
    virtual bool isConst() const = 0;

    /**
    *  @brief
    *    Check if type is an array-type
    *
    *  @return
    *    'true' if type is an array, else 'false'
    */
    virtual bool isArray() const = 0;

    /**
    *  @brief
    *    Check if type is an array of dynamic size
    *
    *  @return
    *    'true' if type is an array of dynamic size, else 'false'
    */
    virtual bool isDynamicArray() const = 0;

    /**
    *  @brief
    *    Check if type is a string-map
    *
    *  @return
    *    'true' if type is a map (e.g., std::map<std::string, T>), else 'false'
    */
    virtual bool isMap() const = 0;

    /**
    *  @brief
    *    Check if type is a boolean
    *
    *  @return
    *    'true' if type is a boolean, else 'false'
    */
    virtual bool isBoolean() const = 0;

    /**
    *  @brief
    *    Check if type is a number
    *
    *  @return
    *    'true' if type is a number, else 'false'
    */
    virtual bool isNumber() const = 0;

    /**
    *  @brief
    *    Check if type is an integral number
    *
    *  @return
    *    'true' if type is an integral number, else 'false'
    */
    virtual bool isIntegral() const = 0;

    /**
    *  @brief
    *    Check if type is an unsigned number
    *
    *  @return
    *    'true' if type is an unsigned number, else 'false'
    */
    virtual bool isUnsigned() const = 0;

    /**
    *  @brief
    *    Check if type is a floating point number
    *
    *  @return
    *    'true' if type is a floating point number, else 'false'
    */
    virtual bool isFloatingPoint() const = 0;

    /**
    *  @brief
    *    Check if type is a string
    *
    *  @return
    *    'true' if type is a string, else 'false'
    */
    virtual bool isString() const = 0;
};


} // namespace cppexpose


#include <cppexpose/type/AbstractTyped.inl>
