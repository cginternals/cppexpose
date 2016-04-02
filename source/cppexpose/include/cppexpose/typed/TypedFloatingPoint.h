
#pragma once


#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a floating point value
*/
template <typename T>
class TypedFloatingPoint : public Typed<T>
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
    virtual bool isNumber() const override;
    virtual bool isFloatingPoint() const override;
};


} // namespace cppexpose


#include <cppexpose/typed/TypedFloatingPoint.hpp>
