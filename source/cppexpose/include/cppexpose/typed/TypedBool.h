
#pragma once


#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a boolean value
*/
template <typename T>
class TypedBool : public Typed<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedBool();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedBool();

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
    virtual bool isBool() const override;
};


} // namespace cppexpose


#include <cppexpose/typed/TypedBool.hpp>
