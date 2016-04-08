
#pragma once


#include <vector>
#include <unordered_map>

#include <cppexpose/typed/AbstractTyped.h>
#include <cppexpose/reflection/Property.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for reflection-enabled objects
*/
class CPPEXPOSE_API PropertyGroup : public AbstractTyped, public AbstractProperty
{
public:
    // [TODO]
//  signalzeug::Signal<size_t, AbstractProperty *> beforeAdd;   ///< Called, before a property is added to the group
//  signalzeug::Signal<size_t, AbstractProperty *> afterAdd;    ///< Called, after a property is added to the group
//  signalzeug::Signal<size_t> beforeRemove;                    ///< Called, before a property is removed from the group
//  signalzeug::Signal<size_t> afterRemove;                     ///< Called, after a property is removed from the group
    void beforeAdd(size_t index, AbstractProperty * property);
    void afterAdd(size_t index, AbstractProperty * property);
    void beforeRemove(size_t index);
    void afterRemove(size_t index);


public:
    //@{
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name
    */
    PropertyGroup(const std::string & name);

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
    *    If m_ownsProperties is 'true', the removed properties are deleted.
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
    *    Get property
    *
    *  @param[in] path
    *    Path of property relative to the group, e.g. "Prop1", or "Sub1/Sub2/Property"
    *
    *  @return
    *    Pointer to the property, or nullptr on error
    */
    AbstractProperty * property(const std::string & path);
    const AbstractProperty * property(const std::string & path) const;

    template <typename Type>
    Property<Type> * property(const std::string & path);

    template <typename Type>
    const Property<Type> * property(const std::string & path) const;
    //@}

    //@{
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
    *    Add property
    *
    *  @param[in] property
    *    Property
    *
    *  @return
    *    Pointer to the new property, or nullptr on error
    */
    AbstractProperty * addProperty(AbstractProperty * property);

    /**
    *  @brief
    *    Create and add property
    *
    *  @param[in] name
    *    Property name
    *  @param[in] args
    *    Property arguments
    *
    *  @return
    *    Pointer to the new property, or nullptr on error
    */
    template <typename Type, typename... Args>
    Property<Type> * addProperty(const std::string & name, Args&&... args);

    /**
    *  @brief
    *    Create and add property group
    *
    *  @param[in] name
    *    Name of property group
    *
    *  @return
    *    Pointer to the new property group, or nullptr on error
    */
    PropertyGroup * addGroup(const std::string & name);
    //@}

    //@{
    /**
    *  @brief
    *    Get property value
    *
    *    Get a property of the group and return its value of type Type.
    *    If the property is not of the specified type, it will return a default value.
    *
    *  @param[in] path
    *    Path of property relative to the group, e.g. "Prop1", or "Sub1/Sub2/Property"
    *
    *  @return
    *    Value of the property
    */
//    template <typename Type>
//    Type value(const std::string & path) const;

    /**
    *  @brief
    *    Set property value
    *
    *    Set the value of a property of the group.
    *    If the property is not of the specified type, the function will fail.
    *
    *  @param[in] path
    *    Path of property relative to the group, e.g. "Prop1", or "Sub1/Sub2/Property"
    *  @param[in] value
    *    New value
    */
//    template <typename Type>
//    void setValue(const std::string & path, const Type & value);
    //@}

    // Virtual AbstractProperty interface
    virtual AbstractTyped * asTyped() override;
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
    std::vector<AbstractProperty *>                     m_properties;    ///< List of properties in the group
    std::unordered_map<std::string, AbstractProperty *> m_propertiesMap; ///< Map of names and properties
    bool m_ownsProperties; ///< [TODO] Remove!
};


} // namespace cppexpose
