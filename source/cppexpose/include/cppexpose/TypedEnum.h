
#pragma once


#include <vector>
#include <map>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Default value mapping for enum type
*
*    Specialize this template to provide a default string mapping for an enum.
*/
template <typename Type>
struct CPPEXPOSE_TEMPLATE_API EnumDefaultStrings
{
    /**
    *  @brief
    *    Return available enum values and their string representations
    *
    *  @return
    *    Map of values and strings
    */
    std::map<Type, std::string> operator()();
};


/**
*  @brief
*    Representation of an enum value
*/
template <typename Type, typename Storage>
class CPPEXPOSE_TEMPLATE_API TypedEnum : public Storage
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
    TypedEnum(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedEnum();

    /**
    *  @brief
    *    Get available enum values as strings
    *
    *  @return
    *    List of values
    */
    std::vector<std::string> strings() const;

    /**
    *  @brief
    *    Set available enum values
    *
    *  @param[in] pairs
    *    List of values and names
    */
    void setStrings(const std::map<Type, std::string> & pairs);

    // Replication
    //   Overloaded in Storage type

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
    virtual bool isObjectPointer() const override;
    virtual bool isArray() const override;
    virtual bool isArrayPointer() const override;
    virtual bool isFunction() const override;

    // Access modifiers
    //   Overloaded in Storage type

    // Value access
    //   Overloaded in Storage type

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

protected:
    std::map<Type, std::string> m_stringMap; ///< Map from enum value -> string
    std::map<std::string, Type> m_enumMap;   ///< Map from string -> enum value
};


} // namespace cppexpose


#include <cppexpose/TypedEnum.inl>
