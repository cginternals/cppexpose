
#pragma once


#include <memory>
#include <string>

#include <cppexpose/signal/Signal.h>
#include <cppexpose/variant/Variant.h>
#include <cppexpose/type/AbstractValueContainer.h>


namespace cppexpose
{


class Object;
class AbstractValueContainer;


/**
*  @brief
*    Base class for properties
*/
class CPPEXPOSE_API AbstractProperty2 : public AbstractValueContainer
{
    friend class Object;


public:
    Signal<AbstractProperty2 *> beforeDestroy; ///< Called before a property is destroyed


public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractProperty2();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractProperty2();

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
    *    Set name
    *
    *  @param[in] name
    *    Name
    *
    *  @remarks
    *    This function should never be called after the property has been added to
    *    a parent object. The name change will not be updated in the parent container.
    */
    void setName(const std::string & name);

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
    *    Finds out whether the Object has a parent
    *
    *  @return
    *    false if the parent is null, otherwise true
    */
    bool hasParent() const;

    /**
    *  @brief
    *    Check if property is an object
    *
    *  @return
    *    'true' if property is an object, else 'false'
    */
    virtual bool isObject() const = 0;

    // Virtual AbstractBaseType interface
    virtual std::string typeName() const override;
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
    virtual const AbstractBaseType & type() const override;
    virtual std::unique_ptr<AbstractValueContainer> createCopy() const override;
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
    /**
    *  @brief
    *    Initialize property
    *
    *  @param[in] name
    *    Name (can be empty)
    *  @param[in] parent
    *    Parent object (can be null)
    *
    *  @remarks
    *    The internal parent is updated to the parent parameter.
    *    Do not set m_parent before calling this function, otherwise
    *    the property might be rejected when added to the parent.
    */
    void initProperty(const std::string & name, Object * parent);

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
    std::string                             m_name;   ///< Name of the property
    Object                                * m_parent; ///< Parent object
    std::unique_ptr<AbstractValueContainer> m_value;  ///< Typed value
};


} // namespace cppexpose
