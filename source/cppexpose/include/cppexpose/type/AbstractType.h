
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Base interface for accessing types
*
*    This interface allows for accessing and querying information about
*    data types. It is used for both types and typed values.
*/
class CPPEXPOSE_API AbstractType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractType();

    /**
    *  @brief
    *    Get type instance
    *
    *  @return
    *    Type object
    */
    virtual const AbstractType & type() const = 0;

    /**
    *  @brief
    *    Get type of elements
    *
    *  @return
    *    Element type
    *
    *  @remarks
    *    For array types, this returns the type of the items of the array.
    *    For all other types, the original type is returned.
    */
    virtual const AbstractType & elementType() const = 0;

    /**
    *  @brief
    *    Get RTTI type information
    *
    *  @return
    *    RTTI Type information
    */
    virtual const std::type_info & typeInfo() const = 0;

    /**
    *  @brief
    *    Get type name
    *
    *  @return
    *    Type name
    */
    virtual std::string typeName() const = 0;

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

    /**
    *  @brief
    *    Check if type is a type
    *
    *  @return
    *    'true' if type is a type, else 'false'
    */
    virtual bool isType() const = 0;
};


} // namespace cppexpose
