
#pragma once


#include <string>
#include <map>

#include <cppexpose/type/Type.h>
#include <cppexpose/type/BaseType.h>


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

    // Access functions to the concrete type
    const std::map<std::string, T> & namedValues() const;
    void setNamedValues(const std::map<std::string, T> & namedValues);
    const T & defaultValue() const;
    const T & minimumValue() const;
    void setMinimumValue(const T & value);
    const T & maximumValue() const;
    void setMaximumValue(const T & value);
};


} // namespace cppexpose


#include <cppexpose/type/ConcreteType.inl>
