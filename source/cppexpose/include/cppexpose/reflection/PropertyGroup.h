
#pragma once


#include <vector>
#include <unordered_map>
#include <algorithm>

#include <cppexpose/signal/Signal.h>
#include <cppexpose/typed/AbstractTyped.h>
#include <cppexpose/reflection/DynamicProperty.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for reflection-enabled objects
*/
class CPPEXPOSE_API PropertyGroup : public AbstractProperty
{
    friend class AbstractProperty;


public:
    Signal<size_t, AbstractProperty *> beforeAdd;    ///< Called before a property is added to the group
    Signal<size_t, AbstractProperty *> afterAdd;     ///< Called after a property is added to the group
    Signal<size_t, AbstractProperty *> beforeRemove; ///< Called before a property is removed from the group
    Signal<size_t, AbstractProperty *> afterRemove;  ///< Called after a property is removed from the group


public:
    //@{
    /**
    *  @brief
    *    Constructor
    */
    PropertyGroup();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name
    *  @param[in] parent
    *    Parent object (can be null)
    *
    *  @remarks
    *    If parent is valid, the group is automatically added to the
    *    parent object. The ownership is not transferred, so the group
    *    has to be deleted by the caller.
    *
    *    To transfer the ownership to the parent, call this constructor with
    *    parent(nullptr), and use addProperty() on the parent group.
    */
    PropertyGroup(const std::string & name, PropertyGroup * parent = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyGroup();

    /**
    *  @brief
    *    Clear properties
    *
    *    Removes all properties from the group.
    *    Properties which have been added with PropertyOwnership::Parent
    *    are deleted.
    */
    void clear();

    /**
    *  @brief
    *    Get properties
    *
    *  @return
    *    Map of names and properties
    */
    const std::unordered_map<std::string, AbstractProperty *> & properties() const;

    /**
    *  @brief
    *    Check if property exists
    *
    *  @param[in] name
    *    Name of property
    *
    *  @return
    *    'true' if property exists, else 'false'
    */
    bool propertyExists(const std::string & name) const;
    //@}

    //@{
    /**
    *  @brief
    *    Get property by index
    *
    *  @param[in] index
    *    Index of the property
    *
    *  @return
    *    Pointer to the property, or nullptr on error
    */
    AbstractProperty * property(size_t index);
    const AbstractProperty * property(size_t index) const;
    //@}

    //@{
    /**
    *  @brief
    *    Get property by name
    *
    *  @param[in] path
    *    Path of property relative to the group, e.g. "Prop1", or "Sub1/Sub2/Property"
    *
    *  @return
    *    Pointer to the property, or nullptr on error
    */
    AbstractProperty * property(const std::string & path);
    const AbstractProperty * property(const std::string & path) const;
    //@}

    //@{
    /**
    *  @brief
    *    Add property to group
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *  @param[in] ownership
    *    Property ownership
    *
    *  @return
    *    'true' if the property has been added to the group, else 'false'
    *
    *  @remarks
    *    Adds the given property to the group.
    *
    *    The name of the property must be valid and unique to the group,
    *    also the property must not belong to any other group already.
    *    Otherwise, the property will not be added to the group.
    *
    *    If ownership is set to PropertyOwnership::Parent, the group
    *    takes the ownership over the specified property, so the property
    *    will be deleted together with the object in its destructor.
    */
    bool addProperty(AbstractProperty * property, PropertyOwnership ownership);

    /**
    *  @brief
    *    Remove property from group
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    'true' if the property has been removed from the group, else 'false'
    *
    *  @remarks
    *    If the specified property does not belong to the group,
    *    this function will do nothing and return 'false'.
    *
    *    If ownership of the property is set to PropertyOwnership::Parent,
    *    the group will release its ownership over the property and
    *    transfer it back to the caller. The property will not be deleted!
    */
    bool removeProperty(AbstractProperty * property);

    /**
    *  @brief
    *    Destroy property
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    'true' if the property has been destroyed, else 'false'
    *
    *  @remarks
    *    This function destroys the specified property from the group.
    *    It can only be used on properties which are owned by the
    *    property group, i.e., properties created by createDynamicProperty
    *    or add with PropertyOwnership::Parent. Properties which are not
    *    owned by the property group must be deleted by other means,
    *    on destruction they automatically remove themselves from the group.
    */
    bool destroyProperty(AbstractProperty * property);

    /**
    *  @brief
    *    Check if group exists
    *
    *  @param[in] name
    *    Name of property group
    *
    *  @return
    *    'true' if property group exists, else 'false'
    */
    bool groupExists(const std::string & name) const;
    //@}

    //@{
    /**
    *  @brief
    *    Get property group
    *
    *  @param[in] path
    *    Path of property group relative to the group, e.g. "Sub1", or "Sub1/Sub2"
    *
    *  @return
    *    Pointer to the property group, or nullptr on error
    */
    PropertyGroup * group(const std::string & path);
    const PropertyGroup * group(const std::string & path) const;
    //@}

    //@{
    /**
    *  @brief
    *    Create dynamic property
    *
    *  @param[in] name
    *    Property name
    *  @param[in] value
    *    Default value
    *
    *  @return
    *    Pointer to the new property, or nullptr on error
    *
    *  @remarks
    *    This function creates a new dynamic property of the specified
    *    typed and adds it to the property group. It also takes ownership
    *    over the property.
    */
    template <typename T>
    DynamicProperty<T> * createDynamicProperty(const std::string & name, const T & value = T());
    //@}

    // Virtual AbstractProperty interface
    virtual bool isGroup() const override;

    // Virtual AbstractTyped interface
    virtual AbstractTyped * clone() const;
    virtual const std::type_info & type() const;
    virtual std::string typeName() const;
    virtual bool isReadOnly() const;
    virtual bool isComposite() const;
    virtual size_t numSubValues() const;
    virtual AbstractTyped * subValue(size_t i);
    virtual bool isEnum() const override;
    virtual bool isArray() const override;
    virtual bool isVariant() const override;
    virtual bool isString() const override;
    virtual bool isBool() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isSignedIntegral() const override;
    virtual bool isUnsignedIntegral() const override;
    virtual bool isFloatingPoint() const override;
    virtual Variant toVariant() const override;
    virtual bool fromVariant(const Variant & value) override;
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & value) override;
    virtual bool toBool() const override;
    virtual bool fromBool(bool value) override;
    virtual long long toLongLong() const override;
    virtual bool fromLongLong(long long value) override;
    virtual unsigned long long toULongLong() const override;
    virtual bool fromULongLong(unsigned long long value) override;
    virtual double toDouble() const override;
    virtual bool fromDouble(double value) override;


protected:
    const AbstractProperty * findProperty(const std::vector<std::string> & path) const;


protected:
    std::vector<AbstractProperty *>                     m_properties;        ///< List of properties in the group
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap;     ///< Map of names and properties
    std::vector<AbstractProperty *>                     m_managedProperties; ///< Property that are managed by the property group
};


} // namespace cppexpose


#include <cppexpose/reflection/PropertyGroup.hpp>
