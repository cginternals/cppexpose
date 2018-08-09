
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
    *    Get parent property container
    *
    *  @return
    *    Parent property container (can be null)
    */
    PropertyContainer * parent() const;

protected:
    /**
    *  @brief
    *    Register property at a parent container
    *
    *  @param[in] name
    *    Name (can be empty)
    *  @param[in] parent
    *    Parent container (can be null)
    *
    *  @remarks
    *    The internal parent is updated to the parent parameter.
    *    Do not set m_parent before calling this function, otherwise
    *    the property might be rejected when added to the parent.
    */
    void registerProperty(const std::string & name, PropertyContainer * parent);

protected:
    PropertyContainer * m_parent; ///< Parent property container (can be null)
};


} // namespace cppexpose
