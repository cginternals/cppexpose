
#pragma once


#include <memory>
#include <string>
#include <vector>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a basic type
*
*    This is the base class for type representations, all specific type
*    implementations must derive from this class.
*/
class CPPEXPOSE_API AbstractBaseType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractBaseType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractBaseType();

    /**
    *  @brief
    *    Create a copy of the type
    *
    *  @return
    *    Type
    */
    virtual std::shared_ptr<AbstractBaseType> createCopy() const = 0;

    /**
    *  @brief
    *    Check if an element type exists
    *
    *  @return
    *    'true' if type has a type for its elements, else 'false'
    *
    *  @remarks
    *    This shall return 'true' for container types, otherwise 'false'.
    */
    virtual bool hasElementType() const = 0;

    /**
    *  @brief
    *    Get type of elements
    *
    *  @return
    *    Base type (can be null)
    *
    *  @remarks
    *    For container types, this returns the type of the items of the container.
    *    For all other types, it shall return nullptr.
    */
    virtual std::shared_ptr<AbstractBaseType> elementType() = 0;

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

    /**
    *  @brief
    *    Check if there are symbolic names defined for the data type
    *
    *  @return
    *    'true' if type has symbolic names, else 'false'
    */
    virtual bool hasSymbolicNames() const = 0;

    /**
    *  @brief
    *    Get symbolic names defined for the data type
    *
    *  @return
    *    List of symbolic names
    */
    virtual std::vector<std::string> symbolicNames() const = 0;
};


} // namespace cppexpose
