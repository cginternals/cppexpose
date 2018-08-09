
#pragma once


#include <cppexpose/expose/AbstractVar.h>


namespace cppexpose
{


class PropertyContainer;


/**
*  @brief
*    Abstract base class for properties
*/
class CPPEXPOSE_API AbstractProperty : public AbstractVar
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractProperty();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractProperty();

    /**
    *  @brief
    *    Get parent property
    *
    *  @return
    *    Parent object or array (can be null)
    */
    PropertyContainer * parent() const;

protected:
    void registerProperty(const std::string & name, PropertyContainer * parent);

protected:
    PropertyContainer * m_parent; ///< Parent object or array (can be null)
};


} // namespace cppexpose
