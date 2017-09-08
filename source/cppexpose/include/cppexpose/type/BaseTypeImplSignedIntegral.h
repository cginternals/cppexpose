
#pragma once


#include <cppexpose/type/BaseTypeImplNumber.h>


namespace cppexpose
{


/**
*  @brief
*    Implementation helper for signed integral number types
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API BaseTypeImplSignedIntegral : public BaseTypeImplNumber<T>
{
public:
    typedef T ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    BaseTypeImplSignedIntegral();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~BaseTypeImplSignedIntegral();

    // Virtual AbstractBaseType interface
    virtual std::string typeName() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;

    // Virtual BaseTypeImpl<T, T> interface
    virtual const T & defaultValue() const override;
};


} // namespace cppexpose


#include <cppexpose/type/BaseTypeImplSignedIntegral.inl>
