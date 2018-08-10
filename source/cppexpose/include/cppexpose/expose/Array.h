
#pragma once


#include <memory>
#include <vector>

#include <cppexpose/expose/PropertyContainer.h>


namespace cppexpose
{


template <typename Type>
class Property;


/**
*  @brief
*    Array (list of properties)
*/
class CPPEXPOSE_API Array : public PropertyContainer
{
public:
    //@{
    /**
    *  @brief
    *    Create new array
    *
    *  @return
    *    Unique pointer to new array
    */
    static std::unique_ptr<Array> create();
    //@}

public:
    //@{
    /**
    *  @brief
    *    Constructor
    */
    Array();

    /**
    *  @brief
    *    Copy Constructor
    *
    *  @param[in] arr
    *    Array that will be copied
    */
    Array(const Array & arr);

    /**
    *  @brief
    *    Constructor adding the object to a parent container
    *
    *  @param[in] name
    *    Object name
    *  @param[in] parent
    *    Parent container (must NOT be null!)
    */
    Array(const std::string & name, PropertyContainer * parent);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Array();

    /**
    *  @brief
    *    Check if array is empty
    *
    *  @return
    *    'true' if array is empty, else 'false'
    */
    bool empty() const;

    /**
    *  @brief
    *    Get size of array
    *
    *  @return
    *    Number of elements in the array
    */
    size_t size() const;
    //@}

    //@{
    /**
    *  @brief
    *    Get element at index
    *
    *  @param[in] index
    *    Property index
    *
    *  @return
    *    Property (can be null)
    */
    const AbstractProperty * at(size_t index) const;
    AbstractProperty * at(size_t index);
    //@}

    //@{
    /**
    *  @brief
    *    Add element to array
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    Pointer to the property
    *
    *  @remarks
    *    Adds the given property to the array.
    *    The array will not take ownership over the property.
    */
    AbstractProperty * push(AbstractProperty * property);

    AbstractProperty * push(AbstractProperty && property);

    /**
    *  @brief
    *    Add element to array
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    Pointer to the property
    *
    *  @remarks
    *    Adds the given property to the array and transfers ownership.
    */
    AbstractProperty * push(std::unique_ptr<AbstractProperty> && property);

    /**
    *  @brief
    *    Create and add property to array
    *
    *  @param[in] args
    *    Property constructor arguments
    *
    *  @return
    *    Pointer to the property
    *
    *  @remarks
    *    Creates a property of the given type with the given arguments and adds it to the array.
    *    The array will take ownership over the property.
    */
    template <typename Type, typename... Args>
    bool createElement(Args&&... args);

    /**
    *  @brief
    *    Remove element from array
    *
    *  @param[in] property
    *    Property (must NOT be null!)
    *
    *  @return
    *    'true' if the property has been removed from the array, else 'false'
    *
    *  @remarks
    *    If the specified property does not belong to the array,
    *    this function will do nothing and return 'false'.
    *    If the array has ownership of the property, it will be deleted.
    */
    bool remove(AbstractProperty * property);
    //@}

    // Replication
    virtual AbstractVar * clone() const override;
    virtual std::unique_ptr<AbstractVar> move() override;

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
    virtual const Array * asArray() const override;
    virtual Array * asArray() override;

protected:
    //@{
    /**
    *  @brief
    *    Duplicate array by copying all of its elements
    *
    *  @param[in] arr
    *    Source array
    */
    void copyFromArray(const Array & arr);
    //@}

protected:
    std::vector<AbstractProperty *>                m_properties;    ///< List of properties
    std::vector<std::unique_ptr<AbstractProperty>> m_ownProperties; ///< Properties that are owned by the array
};


} // namespace cppexpose


#include <cppexpose/expose/Array.inl>
