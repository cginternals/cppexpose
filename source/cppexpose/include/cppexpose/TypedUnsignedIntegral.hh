
#pragma once


#include <cppexpose/ValueStorage.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of an unsigned integral value
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API TypedUnsignedIntegral : public AbstractTypedNumber<Type>
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
    TypedUnsignedIntegral(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedUnsignedIntegral();

    // Replication
    //    Overloaded in AbstractTypedNumber

    // Variable type
    virtual std::string typeName() const override;
    virtual bool isIntegral() const override;
    virtual bool isSignedIntegral() const override;
    virtual bool isFloatingPoint() const override;

    // Access modifiers
    //   Overloaded in ValueStorage

    // Value access
    //   Overloaded in ValueStorage

    // Conversion to other types
    //    Overloaded in AbstractTypedNumber

    // Conversion from other types
    virtual bool canConvertFromVar(const AbstractVar & value) override;
    virtual void fromVar(const AbstractVar & value) override;
};


} // namespace cppexpose
