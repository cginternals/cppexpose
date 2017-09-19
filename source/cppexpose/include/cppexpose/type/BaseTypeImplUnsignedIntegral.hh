
#pragma once


#include <cppexpose/type/BaseTypeImplNumber.h>


namespace cppexpose
{


/**
*  @brief
*    Implementation helper for unsigned integral number types
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API BaseTypeImplUnsignedIntegral : public BaseTypeImplNumber<T>
{
public:
    using ElementType = T;


public:
    /**
    *  @brief
    *    Constructor
    */
    BaseTypeImplUnsignedIntegral();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~BaseTypeImplUnsignedIntegral();

    // Virtual AbstractBaseType interface
    virtual const std::string & typeName() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;

    // Virtual BaseTypeImpl<T, T> interface
    virtual const T & defaultValue() const override;
};


} // namespace cppexpose
