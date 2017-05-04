
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/typed/TypedNumber.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a floating point value
*/
template <typename T, typename BASE>
class CPPEXPOSE_TEMPLATE_API TypedFloatingPoint : public TypedNumber<T, BASE>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedFloatingPoint();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedFloatingPoint();

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
    virtual bool isFloatingPoint() const override;
};


} // namespace cppexpose
