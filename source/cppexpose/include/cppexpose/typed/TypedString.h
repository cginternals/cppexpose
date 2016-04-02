
#pragma once


#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a string value
*/
template <typename T>
class TypedString : public Typed<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedString();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedString();

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
    virtual bool isString() const override;
};


} // namespace cppexpose


#include <cppexpose/typed/TypedString.hpp>
