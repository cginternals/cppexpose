
#pragma once


#include <string>

#include <cppexpose/typed/AbstractTyped.h>


namespace cppexpose
{


class PropertyGroup;


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
    PropertyGroup * parent() const;

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
    */
    void initProperty(const std::string & name, PropertyGroup * parent);


protected:
    std::string     m_name;   ///< Name of the property
    PropertyGroup * m_parent; ///< Parent object
};


} // namespace cppexpose
