
#pragma once


#include <cppexpose/expose/AbstractVar.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for objects that contain properties
*/
class CPPEXPOSE_API PropertyContainer : public AbstractVar
{
public:
    //@{
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
    //@}

    //@{
    /**
    *  @brief
    *    Get pointer to container as Object
    *
    *  @return
    *    Pointer to object, or null if container is not of type Object
    */
    virtual const Object * asObject() const;
    virtual Object * asObject();
    //@}

    //@{
    /**
    *  @brief
    *    Get pointer to container as Array
    *
    *  @return
    *    Pointer to array, or null if container is not of type Array
    */
    virtual const Array * asArray() const;
    virtual Array * asArray();
    //@}
};


} // namespace cppexpose
