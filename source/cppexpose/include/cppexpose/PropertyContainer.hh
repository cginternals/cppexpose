
#pragma once


#include <cppexpose/AbstractVar.hh>


namespace cppexpose
{


/**
*  @brief
*    Base class for objects that contain properties
*/
class CPPEXPOSE_API PropertyContainer : public AbstractVar
{
public:
    /**
    *  @brief
    *    Constructor
    */
    PropertyContainer();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyContainer();
};


} // namespace cppexpose
