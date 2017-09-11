
#pragma once


#include <string>

#include <cppexpose/signal/Signal.h>
#include <cppexpose/value/AbstractValueContainer.h>


namespace cppexpose
{


class Object;


/**
*  @brief
*    Base class for properties
*/
class CPPEXPOSE_API AbstractProperty : public AbstractValueContainer
{
    friend class Object;


public:
    Signal<AbstractProperty *> beforeDestroy; ///< Called before a property is destroyed


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Property name (must NOT be empty!)
    *  @param[in] parent
    *    Parent object (can be null)
    *
    *  @remarks
    *    If parent is valid, the property is automatically added to the
    *    parent object. The ownership is not transferred, so the property
    *    has to be deleted by the caller. To transfer the ownership to the
    *    parent, call this constructor with parent(nullptr) and pass
    *    a unique_ptr to addProperty() on the parent object.
    */
    AbstractProperty(const std::string & name, Object * parent = nullptr);

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
    *    Parent object (can be null)
    */
    Object * parent() const;

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Name
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Check if property is an object
    *
    *  @return
    *    'true' if property is an object, else 'false'
    */
    virtual bool isObject() const = 0;


protected:
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

    /**
    *  @brief
    *    Set name
    *
    *  @param[in] name
    *    Name
    *
    *  @remarks
    *    This function should never be called after the property has been added to
    *    a parent object, as the name change will not be updated in the parent container.
    *    However, Object might call this function to rename a property which would
    *    cause a name conflict when it is added to the container.
    */
    void setName(const std::string & name);


protected:
    Object      * m_parent; ///< Parent object
    std::string   m_name;   ///< Name of the property
};


} // namespace cppexpose
