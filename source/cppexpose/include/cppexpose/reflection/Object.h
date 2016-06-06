
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
    *  @param[in] parent
    *    Parent object (can be null)
    */
    Object(const std::string & name = "", PropertyGroup * parent = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Object();
};


} // namespace cppexpose
