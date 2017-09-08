
#pragma once


#include <cppexpose/type/AbstractBaseType.h>


namespace cppexpose
{


/**
*  @brief
*    The type of all abstract types.
*    The type of the MetaType is a MetaType.
*/
class CPPEXPOSE_API MetaType : public AbstractBaseType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    MetaType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~MetaType();

    // Virtual AbstractBaseType interface
    virtual std::unique_ptr<AbstractBaseType> createCopy() const override;
    virtual std::string typeName() const override;
    virtual bool isNull() const override;
    virtual bool isType() const override;
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
    virtual bool hasElementType() const override;
    virtual std::shared_ptr<AbstractBaseType> elementType() override;
    virtual bool hasSymbolicNames() const override;
    virtual std::vector<std::string> symbolicNames() const override;
};


} // namespace cppexpose
