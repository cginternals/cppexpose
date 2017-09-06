
#pragma once


#include <string>
#include <vector>

#include <cppexpose/type/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for types
*
*    This is the base class for type representations. It can be used to
*    query information about data types and to query generic types.
*/
class CPPEXPOSE_API AbstractType : public Typed
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

    // Virtual Typed interface
    virtual const AbstractType & type() const override = 0;
    virtual const AbstractType & elementType() const override = 0;
    virtual std::string typeName() const override = 0;
    virtual bool isNull() const override = 0;
    virtual bool isConst() const override = 0;
    virtual bool isArray() const override = 0;
    virtual bool isDynamicArray() const override = 0;
    virtual bool isMap() const override = 0;
    virtual bool isBoolean() const override = 0;
    virtual bool isNumber() const override = 0;
    virtual bool isIntegral() const override = 0;
    virtual bool isUnsigned() const override = 0;
    virtual bool isFloatingPoint() const override = 0;
    virtual bool isString() const override = 0;
    virtual bool isType() const override = 0;
    virtual bool hasSymbolicNames() const override = 0;
    virtual std::vector<std::string> symbolicNames() const override = 0;
};


} // namespace cppexpose
