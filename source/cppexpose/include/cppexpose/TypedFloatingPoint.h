
#pragma once


#include <cppexpose/AbstractTypedNumber.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a floating point value
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API TypedFloatingPoint : public AbstractTypedNumber<Type>
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
    TypedFloatingPoint(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedFloatingPoint();

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


#include <cppexpose/TypedFloatingPoint.inl>
