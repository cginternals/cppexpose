
#pragma once


#include <cppexpose/typed/TypedNumber.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a signed integral value
*/
template <typename T>
class TypedSignedIntegral : public TypedNumber<T>
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
    virtual bool isIntegral() const override;
    virtual bool isSignedIntegral() const override;
};


} // namespace cppexpose
