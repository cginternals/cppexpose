
#pragma once


#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of an enum value
*/
template <typename T>
class TypedEnum : public Typed<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedEnum();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedEnum();

    // Virtual Typed<T> interface
    virtual std::string typeName() const override;
};


} // namespace cppexpose


#include <cppexpose/typed/TypedEnum.hpp>
