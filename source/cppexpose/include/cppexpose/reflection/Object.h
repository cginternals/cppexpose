
#pragma once


#include <cppexpose/reflection/PropertyGroup.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for reflection-enabled objects
*/
class CPPEXPOSE_API Object : public PropertyGroup
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name
    */
    Object(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Object();
};


} // namespace cppexpose
