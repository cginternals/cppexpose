
#pragma once


#include <memory>
#include <string>

#include <cppexpose/VarType.h>
#include <cppexpose/Signal.h>


namespace cppexpose
{


class Variant;
class Object;
class Array;
class PropertyContainer;


/**
*  @brief
*    Abstract base class for typed variables
*/
class CPPEXPOSE_API AbstractVar
{
public:
    Signal<> beforeDestroy; ///< Called before a property is destroyed

public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractVar();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractVar();

    /**
    *  @brief
    *    Get parent property container
    *
    *  @return
    *    Parent property container (can be null)
    */
    PropertyContainer * parent() const;

    /**
    *  @brief
    *    Set parent property container
    *
    *  @param[in] parent
    *    Parent property container (can be null)
    *
    *  @remarks
    *    Updates the parent according to the following rules:
    *    - If the variable does not have a parent, and the new parent is not null,
    *      the parent is updated.
    *    - If the variable does have a parent, and the new parent is null,
    *      the parent is removed.
    *    - If the variable already has a parent, and the new parent is different but not null,
    *      the parent is NOT updated.
    */
    void setParent(PropertyContainer * parent);

    /**
    *  @brief
    *    Resolve property by relative path
    *
    *  @param[in] path
    *    Path to property relative to this var, e.g. "prop1", or "sub1.sub2.property", or "parent.val".
    *
    *  @return
    *    Pointer to the property, or nullptr on error
    *
    *  @remarks
    *    To access the parent property, the keyword "parent" can be used.
    */
    const AbstractVar * resolve(const std::string & path) const;

    /**
    *  @brief
    *    Check if value type can be converted
    *
    *  @return
    *    'true' if value can be converted into type Type, else 'false'.
    *
    *  @remarks
    *    Conversion is only supported if the source type is able to convert
    *      into a basic type (number, string, or object), and the destination
    *      type is able to convert from that same basic type.
    */
    template <typename Type>
    bool canConvert() const;

    /**
    *  @brief
    *    Get value converted to type Type
    *
    *  @return
    *    Converted value (or default value for that type)
    *
    *  @remarks
    *    If the conversion fails, the value will be the default value for the given type.
    */
    template <typename Type>
    Type convert() const;

    // Replication

    /**
    *  @brief
    *    Create a copy of the typed value
    *
    *  @return
    *    Pointer to the cloned value
    *
    *  @remarks
    *    The copy of a variable should be a standalone variable
    *    of the same type, i.e., an instance of ValueStorage
    *    of the given type. Do not clone the container type,
    *    such as a property, when implementing clone()
    *    in derived classes.
    */
    virtual std::unique_ptr<AbstractVar> clone() const = 0;

    /**
    *  @brief
    *    Move the contents of the typed value to a new object
    *
    *  @return
    *    Pointer to the moved value
    *
    *  @remarks
    *    The moved value should be of the exact same type
    *    as the source and contain the same content, which
    *    has been moved over to the new object using std::move.
    */
    virtual std::unique_ptr<AbstractVar> move() = 0;

    // Variable type

    /**
    *  @brief
    *    Get type of variable
    *
    *  @return
    *    Type category
    */
    virtual VarType type() const = 0;

    /**
    *  @brief
    *    Get type of variable
    *
    *  @return
    *    Type name
    */
    virtual std::string typeName() const;

    /**
    *  @brief
    *    Check if value is of empty type
    *
    *  @return
    *    'true' if value is of empty type, else 'false'
    */
    virtual bool isNull() const = 0;

    /**
    *  @brief
    *    Check if value is of type bool
    *
    *  @return
    *    'true' if value is a bool, else 'false'
    */
    virtual bool isBool() const = 0;

    /**
    *  @brief
    *    Check if value is a number
    *
    *  @return
    *    'true' if value is a number, else 'false'
    */
    virtual bool isNumber() const = 0;

    /**
    *  @brief
    *    Check if value is an integral
    *
    *  @return
    *    'true' if value is a integral, else 'false'
    */
    virtual bool isIntegral() const = 0;

    /**
    *  @brief
    *    Check if value is a signed integral
    *
    *  @return
    *    'true' if value is a signed integral, else 'false'
    */
    virtual bool isSignedIntegral() const = 0;

    /**
    *  @brief
    *    Check if value is a floating point number
    *
    *  @return
    *    'true' if value is a floating point number, else 'false'
    */
    virtual bool isFloatingPoint() const = 0;

    /**
    *  @brief
    *    Check if value is of enum-type
    *
    *  @return
    *    'true' if value is an enum, else 'false'
    */
    virtual bool isEnum() const = 0;

    /**
    *  @brief
    *    Check if value is of type string
    *
    *  @return
    *    'true' if value is a string, else 'false'
    */
    virtual bool isString() const = 0;

    /**
    *  @brief
    *    Check if value is of an external type (e.g., a class or struct)
    *
    *  @return
    *    'true' if value is an external type, else 'false'
    */
    virtual bool isExternal() const = 0;

    /**
    *  @brief
    *    Check if value is of a pointer type
    *
    *  @return
    *    'true' if value is of pointer type, else 'false'
    */
    virtual bool isPointer() const = 0;

    /**
    *  @brief
    *    Check if value is of type Object
    *
    *  @return
    *    'true' if value is an instance of type Object, else 'false'
    */
    virtual bool isObject() const = 0;

    /**
    *  @brief
    *    Check if value is a pointer to Object
    *
    *  @return
    *    'true' if value is a pointer to Object, else 'false'
    */
    virtual bool isObjectPointer() const = 0;

    /**
    *  @brief
    *    Check if value is of type Array
    *
    *  @return
    *    'true' if value is an instance of type Array, else 'false'
    */
    virtual bool isArray() const = 0;

    /**
    *  @brief
    *    Check if value is a pointer to Array
    *
    *  @return
    *    'true' if value is a pointer to Array, else 'false'
    */
    virtual bool isArrayPointer() const = 0;

    /**
    *  @brief
    *    Check if value is of function type
    *
    *  @return
    *    'true' if value is a function, else 'false'
    */
    virtual bool isFunction() const = 0;

    // Access modifiers

    /**
    *  @brief
    *    Check if value is const (read-only)
    *
    *  @return
    *    'true' if value is read-only, else 'false'
    */
    virtual bool isConst() const = 0;

    // Additional information
    /**
    *  @brief
    *    Get minimum value of accepted value range
    *
    *  @return
    *    Minimum value (should have the same type as the variable)
    *
    *  @remarks
    *    By default, this is only implemented for number types.
    */
    virtual Variant minimumValue() const = 0;

    /**
    *  @brief
    *    Get maximum value of accepted value range
    *
    *  @return
    *    Maximum value (should have the same type as the variable)
    *
    *  @remarks
    *    By default, this is only implemented for number types.
    */
    virtual Variant maximumValue() const = 0;

    // Conversion to other types

    /**
    *  @brief
    *    Check if value can be converted to string
    *
    *  @return
    *    'true' if value can be converted to string, else 'false'
    */
    virtual bool canConvertToString() const = 0;

    /**
    *  @brief
    *    Convert value into string
    *
    *  @return
    *    String representation of the value
    */
    virtual std::string toString() const = 0;

    /**
    *  @brief
    *    Check if value can be converted to boolean
    *
    *  @return
    *    'true' if value can be converted to boolean, else 'false'
    */
    virtual bool canConvertToBool() const = 0;

    /**
    *  @brief
    *    Convert value into bool
    *
    *  @return
    *    Converted value
    */
    virtual bool toBool() const = 0;

    /**
    *  @brief
    *    Check if value can be converted to long long
    *
    *  @return
    *    'true' if value can be converted to long long, else 'false'
    */
    virtual bool canConvertToLongLong() const = 0;

    /**
    *  @brief
    *    Convert value into long long
    *
    *  @return
    *    Converted value
    */
    virtual long long toLongLong() const = 0;

    /**
    *  @brief
    *    Check if value can be converted to unsigned long long
    *
    *  @return
    *    'true' if value can be converted to unsigned long long, else 'false'
    */
    virtual bool canConvertToULongLong() const = 0;

    /**
    *  @brief
    *    Convert value into unsigned long long
    *
    *  @return
    *    Converted value
    */
    virtual unsigned long long toULongLong() const = 0;

    /**
    *  @brief
    *    Check if value can be converted to double
    *
    *  @return
    *    'true' if value can be converted to double, else 'false'
    */
    virtual bool canConvertToDouble() const = 0;

    /**
    *  @brief
    *    Convert value into double
    *
    *  @return
    *    Converted value
    */
    virtual double toDouble() const = 0;

    /**
    *  @brief
    *    Check if value can be converted to an object
    *
    *  @return
    *    'true' if value can be converted to an object, else 'false'
    */
    virtual bool canConvertToObject() const = 0;

    /**
    *  @brief
    *    Convert value into an object
    *
    *  @return
    *    Converted value
    */
    virtual Object toObject() const = 0;

    /**
    *  @brief
    *    Check if value can be converted to an array
    *
    *  @return
    *    'true' if value can be converted to an array, else 'false'
    */
    virtual bool canConvertToArray() const = 0;

    /**
    *  @brief
    *    Convert value into an array
    *
    *  @return
    *    Converted value
    */
    virtual Array toArray() const = 0;

    // Conversion from other types

    /**
    *  @brief
    *    Check if value can be set from another typed value
    *
    *  @param[in] value
    *    Typed value
    *
    *  @return
    *    'true' if value can be converted from the given value, else 'false'
    */
    virtual bool canConvertFromVar(const AbstractVar & value) = 0;

    /**
    *  @brief
    *    Set value from another typed value
    *
    *  @param[in] value
    *    Typed value
    */
    virtual void fromVar(const AbstractVar & value) = 0;

    // Direct access
    /**
    *  @brief
    *    Get direct access to object
    *
    *  @return
    *    Pointer to object, or nullptr if the variable is no Object
    */
    virtual const Object * asObject() const = 0;

    /**
    *  @brief
    *    Get direct access to array
    *
    *  @return
    *    Pointer to array, or nullptr if the variable is no Array
    */
    virtual const Array * asArray() const = 0;

protected:
    /**
    *  @brief
    *    Register property at a parent container
    *
    *  @param[in] parent
    *    Parent container (can be null)
    *  @param[in] name
    *    Name (can be empty)
    *
    *  @remarks
    *    The internal parent is updated to the parent parameter.
    *    Do not set m_parent before calling this function, otherwise
    *    the property might be rejected when added to the parent.
    */
    void registerProperty(PropertyContainer * parent, const std::string & name);


protected:
    PropertyContainer * m_parent; ///< Parent property container (can be null)
};


} // namespace cppexpose


#include <cppexpose/AbstractVar.inl>
