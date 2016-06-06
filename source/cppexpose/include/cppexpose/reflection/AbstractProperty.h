
#pragma once


#include <string>

#include <cppexpose/signal/Signal.h>
#include <cppexpose/typed/AbstractTyped.h>


namespace cppexpose
{


class Object;


/**
*  @brief
*    Defines the ownership for a property, group, or object
*/
enum class PropertyOwnership
{
    None = 0 ///< The property is owner by itself (or outside)
  , Parent   ///< The property is owned by its parent
};


/**
*  @brief
*    Base class for properties
*/
class CPPEXPOSE_API AbstractProperty : public AbstractTyped
{
    friend class Object;


public:
    Signal<AbstractProperty *> beforeDestroy;    ///< Called before a property is destroyed


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
    *    Get name
    *
    *  @return
    *    Name
    */
    std::string name() const;

    /**
    *  @brief
    *    Get parent object
    *
    *  @return
    *    Parent (can be null)
    */
    Object * parent() const;

    /**
    *  @brief
    *    Check if property is a group
    *
    *  @return
    *    'true' if property is a property group, else 'false'
    */
    virtual bool isGroup() const = 0;


protected:
    /**
    *  @brief
    *    Initialize property
    *
    *  @param[in] name
    *    Name (can be empty)
    *  @param[in] parent
    *    Parent object (can be null)
    *  @param[in] ownership
    *    Property ownership
    *
    *  @remarks
    *    The internal parent is updated to the parent parameter.
    *    Do not set m_parent before calling this function, otherwise
    *    the property might be rejected when added to the parent.
    */
    void initProperty(const std::string & name, Object * parent, PropertyOwnership ownership);

    /**
    *  @brief
    *    Set parent object
    *
    *  @param[in] parent
    *    Parent object (can be null)
    *
    *  @remarks
    *    This function should only be called by Object
    *    when adding or removing properties.
    */
    void setParent(Object * parent);


protected:
    std::string   m_name;   ///< Name of the property
    Object      * m_parent; ///< Parent object
};


} // namespace cppexpose
