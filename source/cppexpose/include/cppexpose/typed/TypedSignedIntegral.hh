
#pragma once


#include <cppexpose/typed/TypedNumber.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a signed integral value
*/
template <typename T, typename BASE>
class TypedSignedIntegral : public TypedNumber<T, BASE>
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
