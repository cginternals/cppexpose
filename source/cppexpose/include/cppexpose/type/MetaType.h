
#pragma once


#include <cppexpose/type/AbstractType.h>


namespace cppexpose
{


/**
*  @brief
*    The type of all abstract types.
*    The type of the MetaType is a MetaType.
*/
class CPPEXPOSE_API MetaType : public AbstractType
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

    // Virtual AbstractType interface
    virtual std::unique_ptr<AbstractType> createCopy() const override;
    virtual AbstractType & type() override;
    virtual AbstractType & elementType() override;
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
    virtual bool hasSymbolicNames() const override;
    virtual std::vector<std::string> symbolicNames() const override;
};


} // namespace cppexpose
