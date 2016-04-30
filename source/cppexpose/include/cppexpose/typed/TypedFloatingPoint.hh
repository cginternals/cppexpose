
#pragma once


#include <cppexpose/typed/TypedNumber.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a floating point value
*/
template <typename T>
class TypedFloatingPoint : public TypedNumber<T>
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
