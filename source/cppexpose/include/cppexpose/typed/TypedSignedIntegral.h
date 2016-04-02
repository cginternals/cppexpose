
#pragma once


#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a signed integral value
*/
template <typename T>
class TypedSignedIntegral : public Typed<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedSignedIntegral();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedSignedIntegral();

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isSignedIntegral() const override;
};


} // namespace cppexpose


#include <cppexpose/typed/TypedSignedIntegral.hpp>
