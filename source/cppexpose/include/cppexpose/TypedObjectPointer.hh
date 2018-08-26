
#pragma once


#include <cppexpose/ValueStorage.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a pointer to an Object
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API TypedObjectPointer : public ValueStorage<Type>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    TypedObjectPointer(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedObjectPointer();

    // Replication
    //   Overloaded in ValueStorage

    // Variable type
    virtual VarType type() const override;
    virtual std::string typeName() const override;
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
    virtual bool isObjectPointer() const override;
    virtual bool isArray() const override;
    virtual bool isArrayPointer() const override;
    virtual bool isFunction() const override;

    // Access modifiers
    //   Overloaded in ValueStorage

    // Value access
    //   Overloaded in ValueStorage

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

    // Direct access
    virtual const Object * asObject() const override;
    virtual const Array * asArray() const override;
};


} // namespace cppexpose
