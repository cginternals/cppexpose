
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/typed/TypedNumber.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of an unsigned integral value
*/
template <typename T, typename BASE>
class CPPEXPOSE_TEMPLATE_API TypedUnsignedIntegral : public TypedNumber<T, BASE>
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
