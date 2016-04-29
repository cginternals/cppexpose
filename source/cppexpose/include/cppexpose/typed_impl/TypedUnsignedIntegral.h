
#pragma once


#include <cppexpose/typed_impl/TypedNumber.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of an unsigned integral value
*/
template <typename T>
class TypedUnsignedIntegral : public TypedNumber<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedUnsignedIntegral();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedUnsignedIntegral();

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsignedIntegral() const override;
};


} // namespace cppexpose
