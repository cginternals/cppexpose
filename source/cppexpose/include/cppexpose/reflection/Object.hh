
#pragma once


#include <vector>
#include <unordered_map>
#include <algorithm>

#include <cppexpose/signal/Signal.h>
#include <cppexpose/reflection/Property.hh>
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
    *
    *  @param[in] name
    *    Object name (must NOT be empty!)
    *  @param[in] parent
    *    Parent object (can be null)
    *
    *  @remarks
    *    If parent is valid, the object is automatically added to the
    *    parent object. The ownership is not transferred, so the object
    *    has to be deleted by the caller. To transfer the ownership to the
    *    parent, call this constructor with parent(nullptr) and pass
    *    a unique_ptr to addProperty() on the parent object.
    */
    Object(const std::string & name = "", Object * parent = nullptr);

    /**
    *  @brief
    *    Copy constructor (deleted)
    *
    *  @param[in]
    *    Object to copy from
    */
    Object(const Object &) = delete;

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Object();

    /**
    *  @brief
    *    Copy assignment operator (deleted)
    *
    *  @param[in]
    *    Object to copy from
    */
    Object & operator=(const Object &) = delete;

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
    *    Properties which have been added with a transfer of
    *    ownership are deleted.
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
    *
    *  @return
    *    'true' if the property has been added to the object, else 'false'
    *
    *  @remarks
    *    The name of the property must be valid and unique to the object,
    *    also the property must not belong to any other object already.
    *    Otherwise, the property will not be added to the object.
    */
    bool addProperty(AbstractProperty * property);

    /**
    *  @brief
    *    Add property to object
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    'true' if the property has been added to the object, else 'false'
    *
    *  @remarks
    *    Adds the given property to the object and takes ownership
    *    over the property.
    */
    bool addProperty(std::unique_ptr<AbstractProperty> && property);

    /**
    *  @brief
    *    Create and add property to object
    *
    *  @param[in] name
    *    Name of the new property
    *
    *  @param[in] arguments
    *    Property constructor arguments
    *
    *  @return
    *    'true' if the property has been added to the object, else 'false'
    *
    *  @remarks
    *    Creates a property of the given type with the given arguments and adds it to the object.
    *    The object takes ownership over the new property.
    *    The name of the property must be valid and unique to the object,
    *    also the property must not belong to any other object already,
    *    otherwise, the property will not be added to the object.
    */
    template <typename Type, typename ... Arguments>
    bool createProperty(const std::string & name, Arguments && ... arguments);

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
    *    If the object has ownership of the property, it will be deleted.
    */
    bool removeProperty(AbstractProperty * property);

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
    *    Add (export) static function
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

    /**
    *  @brief
    *    Add (export) const method on object
    *
    *  @param[in] name
    *    Function name
    *  @param[in] obj
    *    Pointer to object instance
    *  @param[in] member
    *    Method pointer
    */
    template <class T, typename RET, typename... Arguments>
    void addFunction(const std::string & name, T * obj, RET (T::*fn)(Arguments...) const);
    //@}

    // Virtual Typed interface
    virtual const Type & type() const override;
    virtual Type & type() override;
    virtual const AbstractBaseType * baseType() const override;
    virtual AbstractBaseType * baseType() override;
    virtual const Type & elementType() const override;
    virtual Type & elementType() override;
    virtual const std::string & typeName() const override;
    virtual bool isNull() const override;
    virtual bool isType() const override;
    virtual bool isConst() const override;
    virtual bool isArray() const override;
    virtual bool isDynamicArray() const override;
    virtual bool isMap() const override;
    virtual bool isBoolean() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;
    virtual bool isString() const override;

    // Virtual AbstractValueContainer interface
    virtual std::unique_ptr<AbstractValueContainer> createCopy() const override;
    virtual bool compareTypeAndValue(const AbstractValueContainer & value) const override;
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
    virtual size_t numElements() const override;
    virtual Variant element(size_t i) const override;
    virtual void setElement(size_t i, const Variant & value) override;
    virtual void pushElement(const Variant & value) override;
    virtual std::vector<std::string> keys() const override;
    virtual Variant element(const std::string & key) const override;
    virtual void setElement(const std::string & key, const Variant & value) override;

    // Virtual AbstractProperty interface
    virtual bool isObject() const override;

    //@{
    /**
    *  @brief
    *    Get the relative path to another object
    *
    *  @param[in] other
    *    The other object
    *
    *  @return
    *    The relative path to the other object
    *
    *  @remarks
    *    Parent-relationships are indicated using "parent"
    *    If no path could be found, the returned string is empty
    *    If this == other, the returned string is "."
    */
    std::string relativePathTo(const Object * const other) const;
    //@}


protected:
    const AbstractProperty * findProperty(const std::vector<std::string> & path) const;


protected:
    std::string                                         m_className;         ///< Class name for this object (default: "Object")
    std::vector<AbstractProperty *>                     m_properties;        ///< List of properties in the object
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap;     ///< Map of names and properties
    std::vector<std::unique_ptr<AbstractProperty>>      m_managedProperties; ///< Property that are owned by the object
    std::vector<Method>                                 m_functions;         ///< List of exported functions
};


} // namespace cppexpose
