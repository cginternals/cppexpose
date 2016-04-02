
#pragma once


#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of an int value
*/
template <typename T>
class TypedInt : public Typed<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedInt();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedInt();
};


} // namespace cppexpose


#include <cppexpose/typed/TypedInt.hpp>
