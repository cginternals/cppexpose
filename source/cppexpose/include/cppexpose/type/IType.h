
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Base interface for accessing types
*
*    This interface allows for accessing types and typed values.
*/
class CPPEXPOSE_API IType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    IType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~IType();

    // Type information
    virtual const std::type_info & typeInfo() const = 0;
    virtual std::string typeName() const = 0;
    virtual bool isConst() const = 0;
    virtual bool isArray() const = 0;
    virtual bool isDynamicArray() const = 0;
    virtual bool isBoolean() const = 0;
    virtual bool isNumber() const = 0;
    virtual bool isIntegral() const = 0;
    virtual bool isUnsigned() const = 0;
    virtual bool isFloatingPoint() const = 0;
    virtual bool isString() const = 0;
};


} // namespace cppexpose
