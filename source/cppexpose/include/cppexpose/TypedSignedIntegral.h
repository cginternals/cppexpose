
#pragma once


#include <cppexpose/AbstractNumber.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a signed integral value
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API TypedSignedIntegral : public AbstractNumber<Type>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    TypedSignedIntegral(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedSignedIntegral();

    // Replication
    //    Overloaded in AbstractNumber

    // Variable type
    virtual bool isIntegral() const override;
    virtual bool isSignedIntegral() const override;
    virtual bool isFloatingPoint() const override;

    // Access modifiers
    //   Overloaded in ValueStorage

    // Value access
    //   Overloaded in ValueStorage

    // Conversion to other types
    //    Overloaded in AbstractNumber

    // Conversion from other types
    virtual bool canConvertFromVar(const AbstractVar & value) override;
    virtual void fromVar(const AbstractVar & value) override;
};


} // namespace cppexpose


#include <cppexpose/TypedSignedIntegral.inl>
