
#pragma once


#include <cppexpose/type/TypeNumber.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a unsigned integral data type
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API TypeUnsignedIntegral : public TypeNumber<T>
{
public:
    typedef T BaseType;
    typedef T ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    TypeUnsignedIntegral();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypeUnsignedIntegral();

    // Virtual AbstractType interface
    virtual std::string typeName() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;

    // Virtual AbstractTypedType<T, T> interface
    virtual const T & defaultValue() const override;
};


} // namespace cppexpose


#include <cppexpose/type/TypeUnsignedIntegral.inl>
