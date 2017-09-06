
#pragma once


#include <cppexpose/type/AbstractType.h>


namespace cppexpose
{


/**
*  @brief
*    Empty (null) type
*/
class CPPEXPOSE_API TypeNull : public AbstractType
{
public:
    typedef void BaseType;
    typedef void ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    TypeNull();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypeNull();

    // Virtual AbstractType interface
    virtual std::string typeName() const override;
    virtual const AbstractType & elementType() const override;
    virtual bool hasSymbolicNames() const override;
    virtual std::vector<std::string> symbolicNames() const override;
    virtual bool isNull() const override;
    virtual bool isConst() const override;
    virtual bool isArray() const override;
    virtual bool isDynamicArray() const override;
    virtual bool isMap() const override;
    virtual bool isBoolean() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;
    virtual bool isString() const override;
    virtual bool isType() const override;
};


} // namespace cppexpose
