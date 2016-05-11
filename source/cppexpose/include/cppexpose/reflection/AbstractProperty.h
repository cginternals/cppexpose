
#pragma once


#include <string>

#include <cppexpose/typed/AbstractTyped.h>


namespace cppexpose
{


class PropertyGroup;


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
    *    Get parent object
    *
    *  @return
    *    Parent (can be null)
    */
    PropertyGroup * parent() const;

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
    *  @param[in] parent
    *    Parent object (can be null)
    *  @param[in] name
    *    Name (can be empty)
    */
    void initProperty(PropertyGroup * parent, const std::string & name);


protected:
    PropertyGroup * m_parent; ///< Parent object
    std::string     m_name;   ///< Name of the property
};


} // namespace cppexpose
