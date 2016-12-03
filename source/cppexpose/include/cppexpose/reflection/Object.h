
#pragma once


#include <vector>
#include <unordered_map>
#include <algorithm>

#include <cppexpose/signal/Signal.h>
#include <cppexpose/typed/AbstractTyped.h>
#include <cppexpose/reflection/DynamicProperty.h>
#include <cppexpose/reflection/Method.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for reflection-enabled objects
*/
class CPPEXPOSE_API Object : public AbstractProperty
{
    friend class AbstractProperty;


public:
    Signal<size_t, AbstractProperty *> beforeAdd;    ///< Called before a property is added to the object
    Signal<size_t, AbstractProperty *> afterAdd;     ///< Called after a property is added to the object
    Signal<size_t, AbstractProperty *> beforeRemove; ///< Called before a property is removed from the object
    Signal<size_t, AbstractProperty *> afterRemove;  ///< Called after a property is removed from the object

    // [TODO] add before and after add/remove callbacks for functions
    //Signal<size_t, Method *> beforeAdd;            ///< Called before a function is added to the object
    //Signal<size_t, Method *> afterAdd;             ///< Called after a function is added to the object
    //Signal<size_t, Method *> beforeRemove;         ///< Called before a function is removed from the object
    //Signal<size_t, Method *> afterRemove;          ///< Called after a function is removed from the object


public:
    //@{
    /**
    *  @brief
    *    Constructor
    */
    Object();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name
    */
    Object(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Object();

    /**
    *  @brief
    *    Get class name
    *
    *  return
    *    Class name for this object (default: "Object")
    */
    const std::string & className() const;

    /**
    *  @brief
    *    Set class name
    *
    *  @param[in] className
    *    Class name for this object (default: "Object")
    */
    void setClassName(const std::string & className);

    /**
    *  @brief
    *    Clear properties
    *
    *    Removes all properties from the object.
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
    *    Path of property relative to the object, e.g. "Prop1", or "Sub1.Sub2.Property"
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
    *    Add property to object
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *  @param[in] ownership
    *    Property ownership
    *
    *  @return
    *    'true' if the property has been added to the object, else 'false'
    *
    *  @remarks
    *    Adds the given property to the object.
    *
    *    The name of the property must be valid and unique to the object,
    *    also the property must not belong to any other object already.
    *    Otherwise, the property will not be added to the object.
    *
    *    If ownership is set to PropertyOwnership::Parent, the object
    *    takes the ownership over the specified property, so the property
    *    will be deleted together with the object in its destructor.
    */
    bool addProperty(AbstractProperty * property, PropertyOwnership ownership = PropertyOwnership::None);

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
    *    If ownership of the property is set to PropertyOwnership::Parent,
    *    the object will release its ownership over the property and
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
    *    This function destroys the specified property from the object.
    *    It can only be used on properties which are owned by the object,
    *    e.g., properties created by createDynamicProperty or added
    *    with PropertyOwnership::Parent. Properties which are not owned by
    *    the object must be deleted by other means, they will automatically
    *    remove themselves from the object on destruction.
    */
    bool destroyProperty(AbstractProperty * property);

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
    *    typed and adds it to the object. It also takes ownership
    *    over the property.
    */
    template <typename T>
    DynamicProperty<T> * createDynamicProperty(const std::string & name, const T & value = T());
    //@}

    /**
    *  @brief
    *    Get list of functions exported by this object
    *
    *  @return
    *    List of methods
    */
    const std::vector<Method> & functions() const;

    /**
    *  @brief
    *    Add (export) function on object
    *
    *  @param[in] name
    *    Function name
    *  @param[in] fn
    *    Function pointer
    */
    template <typename RET, typename... Arguments>
    void addFunction(const std::string & name, RET (*fn)(Arguments...));

    /**
    *  @brief
    *    Add (export) method on object
    *
    *  @param[in] name
    *    Function name
    *  @param[in] obj
    *    Pointer to object instance
    *  @param[in] member
    *    Method pointer
    */
    template <class T, typename RET, typename... Arguments>
    void addFunction(const std::string & name, T * obj, RET (T::*fn)(Arguments...));

    // Virtual AbstractProperty interface
    virtual bool isObject() const override;

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

    /**
    * @brief
    *    Get the relative path to another object
    *
    * @param[in] other
    *    The other object
    *
    * @return
    *    The relative path to the other object
    *
    * @remarks
    *    Parent-relationships are indicated using "parent"
    *    If no path could be found, the returned string is empty
    *    If this == other, the returned string is "."
    */
    std::string relativePathTo(const Object * const other) const;


protected:
    const AbstractProperty * findProperty(const std::vector<std::string> & path) const;


protected:
    std::string                                         m_className;         ///< Class name for this object (default: "Object")
    std::vector<AbstractProperty *>                     m_properties;        ///< List of properties in the object
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap;     ///< Map of names and properties
    std::vector<AbstractProperty *>                     m_managedProperties; ///< Property that are owned by the object
    std::vector<Method>                                 m_functions;         ///< List of exported functions
};


} // namespace cppexpose


#include <cppexpose/reflection/Object.hpp>
