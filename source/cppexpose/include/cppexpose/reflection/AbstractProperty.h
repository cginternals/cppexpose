
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
class CPPEXPOSE_API AbstractProperty// : public AbstractTyped
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] parent
    *    Parent object (can be null)
    */
    AbstractProperty(PropertyGroup * parent = nullptr);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name
    *  @param[in] parent
    *    Parent object (can be null)
    */
    AbstractProperty(const std::string & name, PropertyGroup * parent = nullptr);

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
    *    Get this object as AbstractTyped-pointer
    *
    *  @return
    *    Pointer to AbstractTyped interface
    */
    virtual AbstractTyped * asTyped() = 0;

    /**
    *  @brief
    *    Get this object as AbstractTyped-pointer
    *
    *  @return
    *    Pointer to AbstractTyped interface
    */
    virtual const AbstractTyped * asTyped() const = 0;

    /**
    *  @brief
    *    Check if property is a group
    *
    *  @return
    *    'true' if property is a property group, else 'false'
    */
    virtual bool isGroup() const = 0;


protected:
    std::string     m_name;   ///< Name of the property
    PropertyGroup * m_parent; ///< Parent object
};


} // namespace cppexpose
