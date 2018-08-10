
#pragma once


#include <memory>
#include <vector>
#include <unordered_map>

#include <cppexpose/expose/PropertyContainer.h>


namespace cppexpose
{


template <typename Type>
class Property;


/**
*  @brief
*    Object (container of properties)
*/
class CPPEXPOSE_API Object : public PropertyContainer
{
public:
    //@{
    /**
    *  @brief
    *    Create new object
    *
    *  @return
    *    Unique pointer to new object
    */
    static std::unique_ptr<Object> create();
    //@}

public:
    //@{
    /**
    *  @brief
    *    Constructor
    */
    Object();

    /**
    *  @brief
    *    Copy Constructor
    *
    *  @param[in] obj
    *    Object that will be copied
    */
    Object(const Object & obj);

    /**
    *  @brief
    *    Constructor adding the object to a parent container
    *
    *  @param[in] name
    *    Object name
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    */
    Object(const std::string & name, PropertyContainer * parent);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Object();

    /**
    *  @brief
    *    Check if object is empty
    *
    *  @return
    *    'true' if object is empty, else 'false'
    */
    bool empty() const;

    /**
    *  @brief
    *    Get properties
    *
    *  @return
    *    Names of all properties
    */
    const std::vector<std::string> & properties() const;

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
    *    Get property by name
    *
    *  @param[in] name
    *    Property name
    *
    *  @return
    *    Property (can be null)
    */
    const AbstractProperty * property(const std::string & name) const;
    AbstractProperty * property(const std::string & name);
    //@}

    //@{
    /**
    *  @brief
    *    Add property to object
    *
    *  @param[in] name
    *    Property name
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    Pointer to the property
    *
    *  @remarks
    *    Adds the given property to the object.
    *
    *    The name of the property must be valid and unique to the object,
    *    also the property must not belong to any other object already.
    *    Otherwise, the property will not be added to the object.
    *    The object will not take ownership over the property.
    */
    AbstractProperty * addProperty(const std::string & name, AbstractProperty * property);

    /**
    *  @brief
    *    Add property to object
    *
    *  @param[in] name
    *    Property name
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    Pointer to the property
    *
    *  @remarks
    *    Adds the given property to the object and transfer ownership.
    *
    *    The name of the property must be valid and unique to the object,
    *    also the property must not belong to any other object already.
    *    Otherwise, the property will not be added to the object.
    *    The object will take ownership over the property.
    */
    AbstractProperty * addProperty(const std::string & name, std::unique_ptr<AbstractProperty> && property);

    /**
    *  @brief
    *    Create and add property to object
    *
    *  @param[in] name
    *    Name of the new property
    *  @param[in] args
    *    Property constructor arguments
    *
    *  @return
    *    Pointer to the property
    *
    *  @remarks
    *    Creates a property of the given type with the given arguments and adds it to the object.
    *
    *    The name of the property must be valid and unique to the object,
    *    also the property must not belong to any other object already.
    *    Otherwise, the property will not be added to the object.
    *    The object will take ownership over the property.
    */
    template <typename Type, typename... Args>
    bool createProperty(const std::string & name, Args&&... args);

    /**
    *  @brief
    *    Remove property from object
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    'true' if the property has been removed from the object, else 'false'
    *
    *  @remarks
    *    If the specified property does not belong to the object,
    *    this function will do nothing and return 'false'.
    *
    *    If the object has ownership of the property, it will be deleted.
    */
    bool removeProperty(AbstractProperty * property);
    //@}

    // Replication
    virtual AbstractVar * clone() const override;

    // Variable type
    virtual VarType type() const override;
    virtual bool isNull() const override;
    virtual bool isBool() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isSignedIntegral() const override;
    virtual bool isFloatingPoint() const override;
    virtual bool isEnum() const override;
    virtual bool isString() const override;
    virtual bool isExternal() const override;
    virtual bool isPointer() const override;
    virtual bool isObject() const override;
    virtual bool isArray() const override;
    virtual bool isFunction() const override;

    // Access modifiers
    virtual bool isConst() const override;

    // Additional information
    virtual Variant minimumValue() const override;
    virtual Variant maximumValue() const override;

    // Conversion to other types
    virtual bool canConvertToString() const override;
    virtual std::string toString() const override;
    virtual bool canConvertToBool() const override;
    virtual bool toBool() const override;
    virtual bool canConvertToLongLong() const override;
    virtual long long toLongLong() const override;
    virtual bool canConvertToULongLong() const override;
    virtual unsigned long long toULongLong() const override;
    virtual bool canConvertToDouble() const override;
    virtual double toDouble() const override;
    virtual bool canConvertToObject() const override;
    virtual Object toObject() const override;
    virtual bool canConvertToArray() const override;
    virtual Array toArray() const override;

    // Conversion from other types
    virtual bool canConvertFromVar(const AbstractVar & value) override;
    virtual void fromVar(const AbstractVar & value) override;

    // Property container
    virtual const Object * asObject() const override;
    virtual Object * asObject() override;

protected:
    //@{
    /**
    *  @brief
    *    Duplicate object by copying all of its properties
    *
    *  @param[in] obj
    *    Source object
    */
    void copyFromObject(const Object & obj);
    //@}

protected:
    std::unordered_map<std::string, AbstractProperty *> m_properties;    ///< Map of names and properties
    std::vector<std::unique_ptr<AbstractProperty>>      m_ownProperties; ///< Properties that are owned by the object
    mutable std::vector<std::string>                    m_propertyNames; ///< List of property names (created on-demand)
};


} // namespace cppexpose


#include <cppexpose/expose/Object.inl>