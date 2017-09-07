
#pragma once


#include <memory>
#include <string>
#include <vector>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for types
*
*    This is the base class for type representations. It can be used to
*    query information about data types and to query generic types.
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
    *    Create copy of the type
    *
    *  @return
    *    Type
    */
    virtual std::unique_ptr<AbstractType> createCopy() const = 0;

    virtual AbstractType & type() = 0;
    virtual AbstractType & elementType() = 0;
    virtual std::string typeName() const = 0;
    virtual bool isNull() const = 0;
    virtual bool isConst() const = 0;
    virtual bool isArray() const = 0;
    virtual bool isDynamicArray() const = 0;
    virtual bool isMap() const = 0;
    virtual bool isBoolean() const = 0;
    virtual bool isNumber() const = 0;
    virtual bool isIntegral() const = 0;
    virtual bool isUnsigned() const = 0;
    virtual bool isFloatingPoint() const = 0;
    virtual bool isString() const = 0;
    virtual bool isType() const = 0;
    virtual bool hasSymbolicNames() const = 0;
    virtual std::vector<std::string> symbolicNames() const = 0;
};


} // namespace cppexpose
