
#pragma once


#include <memory>
#include <vector>
#include <map>
#include <string>

#include <cppexpose/json/JSON.h>
#include <cppexpose/type/AbstractType.h>


namespace cppexpose
{


class AbstractValue;
class Variant2;

template <typename T>
class Value;


/**
*  @brief
*    Variant array (analog to a JSON array)
*/
using VariantArray = std::vector<Variant2>;

/**
*  @brief
*    Variant map (analog to a JSON object)
*/
using VariantMap = std::map<std::string, Variant2>;


/**
*  @brief
*    Variant typed value
*
*    A Variant can be used to store and pass arbitrary typed values in a uniform manner.
*
*    To create a Variant from the list of supported primitive data types, use one of the
*    available constructors. To create a Variant from another data type, use the static
*    function fromValue().
*
*    The type of the stored value can be determined by type() or hasType<Type>().
*    To access the value of a variant, call value<Type>(). If the given data type does not
*    match the stored type, the value may be converted. Note that this only works for the
*    supported primitive data types. To check if a type can be converted, use canConvert<Type>().
*
*    VariantArray and VariantMap can be used to store collections or hierarchies of variants.
*    For simplified usage, use the convenience functions array() or map() to create such variants,
*    and asArray() or asMap() to access their data. These composite variants will automatically
*    be interpreted as JSON arrays or objects within scripting and can be serialized by the
*    JSON tool class.
*/
class CPPEXPOSE_API Variant2 : public IType
{
public:
    //@{
    /**
    *  @brief
    *    Create a variant from an arbitrary typed value
    *
    *  @param[in] value
    *    Value
    *
    *  @return
    *    Variant instance
    */
    template <typename T>
    static Variant2 fromValue(const T & value);

    /**
    *  @brief
    *    Create an empty or specifically sized variant array
    *
    *  @param count
    *    The initial size of the array
    *
    *  @return
    *    Variant instance
    */
    static Variant2 array();
    static Variant2 array(size_t count);

    /**
    *  @brief
    *    Create an empty variant map
    *
    *  @return
    *    Variant instance
    */
    static Variant2 map();
    //@}


public:
    //@{
    /**
    *  @brief
    *    Constructor for an empty value
    */
    Variant2();

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] variant
    *    Variant whose value will be copied
    */
    Variant2(const Variant2 & variant);
    //@}

    /**
    *  @brief
    *    Constructor for a primitive data type
    *
    *  @param[in] value
    *    Primitive value
    */
    //@{
    Variant2(bool value);
    Variant2(char value);
    Variant2(unsigned char value);
    Variant2(short value);
    Variant2(unsigned short value);
    Variant2(int value);
    Variant2(unsigned int value);
    Variant2(long value);
    Variant2(unsigned long value);
    Variant2(long long value);
    Variant2(unsigned long long value);
    Variant2(float value);
    Variant2(double value);
    Variant2(const char * value);
    Variant2(const std::string & value);
    Variant2(const std::vector<std::string> & value);
    Variant2(const VariantArray & array);
    Variant2(const VariantMap & map);
    //@}

    //@{
    /**
    *  @brief
    *    Destructor
    */
    ~Variant2();
    //@}

    //@{
    /**
    *  @brief
    *    Copy operator
    *
    *  @param[in] variant
    *    Variant whose value will be copied
    *
    *  @return
    *    Variant
    */
    Variant2 & operator=(const Variant2 & variant);

    /**
    *  @brief
    *    Check if variant is empty
    *
    *  @return
    *    'true' if variant does not contain a value, else 'false'
    */
    bool isNull() const;

    /**
    *  @brief
    *    Get type of variant value
    *
    *  @return
    *    Type object
    */
    const AbstractType & type() const;

    /**
    *  @brief
    *    Check type of variant value
    *
    *  @return
    *    'true' if variant value has the template type ValueType, else 'false'
    */
    template <typename ValueType>
    bool hasType() const;

    /**
    *  @brief
    *    Check if variant type can be converted
    *
    *  @return
    *    'true' if variant can be converted into type ValueType, else 'false'.
    *
    *  @remarks
    *    Conversion is only supported for the following primitive data types:
    *      bool, char, unsigned char, short, unsigned short, int, unsigned int,
    *      long, unsigned long, long long, unsigned long long, float, double,
    *      std::string
    */
    template <typename ValueType>
    bool canConvert() const;

    /**
    *  @brief
    *    Get stored value
    *
    *  @return
    *    Stored value of type ValueType, or default value if type does not match and cannot be converted
    */
    template <typename T>
    T value() const;
    //@}

    //@{
    /**
    *  @brief
    *    Get pointer to the stored value
    *
    *  @return
    *    Pointer to stored value of type ValueType, or nullptr if type does not match and cannot be converted
    */
    template <typename ValueType>
    ValueType * ptr();
    template <typename ValueType>
    const ValueType * ptr() const;
    //@}

    //@{
    /**
    *  @brief
    *    Get JSON representation of variant
    *
    *  @param[in] outputMode
    *    JSON output mode
    *
    *  @return
    *    JSON representation
    *
    *  @see
    *    JSON
    */
//  std::string toJSON(JSON::OutputMode outputMode = JSON::Compact) const;
    //@}

    // Virtual IType interface
    virtual const std::type_info & typeInfo() const override;
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

    // Value access and conversion
    std::string toString() const;
    bool fromString(const std::string & value);
    bool toBool() const;
    bool fromBool(bool value);
    long long toLongLong() const;
    bool fromLongLong(long long value);
    unsigned long long toULongLong() const;
    bool fromULongLong(unsigned long long value);
    double toDouble() const;
    bool fromDouble(double value);


protected:
    std::unique_ptr<AbstractValue> m_value;
};


} // namespace cppexpose


#include <cppexpose/variant/Variant2.inl>
