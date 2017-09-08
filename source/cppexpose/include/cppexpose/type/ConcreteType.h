
#pragma once


#include <cppexpose/type/Type.h>


namespace cppexpose
{


/**
*  @brief
*    Type information for a concrete type
*
*  @remarks
*    This convenience class can be used to create a type wrapper
*    for a specific C++ type. It is equivalent to creating an
*    object of Type with a shared pointer to an AbstractBaseType.
*/
template <typename T>
class CPPEXPOSE_API ConcreteType : public Type
{
public:
    /**
    *  @brief
    *    Constructor for an empty type
    */
    ConcreteType();

    /**
    *  @brief
    *    Destructor
    */
    ~ConcreteType();
};


} // namespace cppexpose


#include <cppexpose/type/ConcreteType.inl>
