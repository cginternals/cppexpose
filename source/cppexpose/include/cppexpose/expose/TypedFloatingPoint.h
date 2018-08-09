
#pragma once


#include <cppexpose/expose/AbstractNumber.h>


namespace cppexpose
{


/**
*  @brief
*    Floating point number
*/
template <typename Type, typename Storage>
class CPPEXPOSE_TEMPLATE_API TypedFloatingPoint : public AbstractNumber<Type, Storage>
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
    //    Overloaded in AbstractNumber

    // Variable type
    virtual bool isIntegral() const override;
    virtual bool isSignedIntegral() const override;
    virtual bool isFloatingPoint() const override;

    // Access modifiers
    //   Overloaded in Storage type

    // Value access
    //   Overloaded in Storage type

    // Conversion to other types
    //    Overloaded in AbstractNumber

    // Conversion from other types
    virtual bool canConvertFromVar(const AbstractVar & value) override;
    virtual void fromVar(const AbstractVar & value) override;
};


} // namespace cppexpose


#include <cppexpose/expose/TypedFloatingPoint.inl>
