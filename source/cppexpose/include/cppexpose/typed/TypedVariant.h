
#pragma once


#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a variant value
*/
template <typename T>
class TypedVariant : public Typed<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedVariant();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedVariant();

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
    virtual bool isVariant() const override;
};


} // namespace cppexpose


#include <cppexpose/typed/TypedVariant.hpp>
