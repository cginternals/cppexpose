
#pragma once


#include <cppexpose/type/BaseTypeImplNumber.h>


namespace cppexpose
{


/**
*  @brief
*    Implementation helper for floating point number types
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API BaseTypeImplFloatingPoint : public BaseTypeImplNumber<T>
{
public:
    using ElementType = T;


public:
    /**
    *  @brief
    *    Constructor
    */
    BaseTypeImplFloatingPoint();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~BaseTypeImplFloatingPoint();

    // Virtual AbstractBaseType interface
    virtual const std::string & typeName() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;

    // Virtual BaseTypeImpl<T, T> interface
    virtual const T & defaultValue() const override;
};


} // namespace cppexpose


#include <cppexpose/type/BaseTypeImplFloatingPoint.inl>
