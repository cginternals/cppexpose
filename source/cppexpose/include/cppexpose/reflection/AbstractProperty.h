
#pragma once


#include <cppexpose/reflection/Named.h>


namespace cppexpose
{


class AbstractTyped;


/**
*  @brief
*    Base class for properties
*/
class CPPEXPOSE_API AbstractProperty : public Named
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name
    */
    AbstractProperty(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractProperty();

    /**
    *  @brief
    *    Get this object as AbstractTyped-pointer
    *
    *  @return
    *    Pointer to AbstractTyped interface
    */
    virtual AbstractTyped * asTyped() = 0;

    /**
    *  @brief
    *    Check if property is a group
    *
    *  @return
    *    'true' if property is a property group, else 'false'
    */
    virtual bool isGroup() const = 0;
};


} // namespace cppexpose
