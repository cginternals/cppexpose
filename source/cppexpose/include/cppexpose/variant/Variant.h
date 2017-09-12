
#pragma once


#include <memory>
#include <vector>
#include <map>
#include <string>

#include <cppexpose/json/JSON.h>
#include <cppexpose/type/AbstractTyped.h>


namespace cppexpose
{


class AbstractValueContainer;
class Variant;


/**
*  @brief
*    Variant array (analog to a JSON array)
*/
using VariantArray = std::vector<Variant>;

/**
*  @brief
*    Variant map (analog to a JSON object)
*/
using VariantMap = std::map<std::string, Variant>;


/**
*  @brief
*    Variant typed value
*
*    A Variant can be used to store and pass arbitrary typed values in a uniform manner.
*
*    To create a Variant from a specific data type, use the static function fromValue().
*
*    The type of the stored value can be determined by type(), or hasType<Type>().
*    To access the value of a variant, call value<Type>(). If the given data type does not
*    match the stored type, the value may be converted. Note that this only works for the
*    supported primitive data types. To check if a type can be converted, use canConvert<Type>().
*
*    VariantArray and VariantMap can be used to store collections or hierarchies of variants.
*    For simplified usage, use the convenience functions array() or map() to create such variants.
*    These composite variants will automatically be interpreted as JSON arrays or objects within
*    scripting and can be serialized by the JSON tool class.
*/
class CPPEXPOSE_API Variant : public AbstractTyped
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
    static Variant fromValue(const T & value);

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
    static Variant array();
    static Variant array(size_t count);

    /**
    *  @brief
    *    Create an empty variant map
    *
    *  @return
    *    Variant instance
    */
    static Variant map();
    //@}


public:
    //@{
    /**
    *  @brief
    *    Constructor for an empty value
    */
    Variant();

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] variant
    *    Variant whose value will be copied
    */
    Variant(const Variant & variant);
    //@}

    //@{
    /**
    *  @brief
    *    Constructor for a primitive data type
    *
    *  @param[in] value
    *    Primitive value
    */
    Variant(bool value);
    Variant(char value);
    Variant(unsigned char value);
    Variant(short value);
    Variant(unsigned short value);
    Variant(int value);
    Variant(unsigned int value);
    Variant(long value);
    Variant(unsigned long value);
    Variant(long long value);
    Variant(unsigned long long value);
    Variant(float value);
    Variant(double value);
    Variant(const char * value);
    Variant(const std::string & value);
    Variant(const std::vector<std::string> & value);
    Variant(const VariantArray & array);
    Variant(const VariantMap & map);
    //@}

    //@{
    /**
    *  @brief
    *    Destructor
    */
    ~Variant();

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
    Variant & operator=(const Variant & variant);

    /**
    *  @brief
    *    Comparison operator
    *
    *  @param[in] variant
    *    Variant
    *
    *  @return
    *    'true' if variants are equal in type and value, else 'false'
    */
    bool operator==(const Variant & variant) const;

    /**
    *  @brief
    *    Comparison operator
    *
    *  @param[in] variant
    *    Variant
    *
    *  @return
    *    'true' if variants are different in type or value, else 'false'
    */
    bool operator!=(const Variant & variant) const;

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
    template <typename ValueType>
    ValueType value() const;
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

    // Virtual Typed interface
    virtual const Type & type() const override;
    virtual Type & type() override;
    virtual const AbstractBaseType * baseType() const override;
    virtual AbstractBaseType * baseType() override;
    virtual const Type & elementType() const override;
    virtual Type & elementType() override;
    virtual const std::string & typeName() const override;
    virtual bool isNull() const override;
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
    virtual bool isType() const override;

    /**
    *  @brief
    *    Get number of elements of an array
    *
    *  @return
    *    Number of elements, 1 if not an array
    *
    *  @remarks
    *    Only works if the type is an array (see isArray()).
    */
    size_t numElements() const;

    /**
    *  @brief
    *    Get element of an array as variant
    *
    *  @param[in] i
    *    Index of element
    *
    *  @return
    *    Value of element, default value if index is invalid
    *
    *  @remarks
    *    Only works if the type is an array (see isArray()).
    */
    Variant element(size_t i) const;

    /**
    *  @brief
    *    Set element of an array as variant
    *
    *  @param[in] i
    *    Index of element
    *  @param[in] value
    *    Value of element
    *
    *  @remarks
    *    Only works if the type is an array (see isArray()).
    */
    void setElement(size_t i, const Variant & value);

    /**
    *  @brief
    *    Add element as variant to an array
    *
    *  @param[in] value
    *    Value of element
    *
    *  @remarks
    *    Only works if the type is a dynamic array (see isDynamicArray()).
    *    The default implementation of this function does nothing (NOP).
    */
    void pushElement(const Variant & value);

    /**
    *  @brief
    *    Get list of keys of a map
    *
    *  @return
    *    List of keys, empty list if not a map
    *
    *  @remarks
    *    Only works if the type is a map (see isMap()).
    */
    std::vector<std::string> keys() const;

    /**
    *  @brief
    *    Get element of a map as variant
    *
    *  @param[in] key
    *    Key
    *
    *  @return
    *    Value of element, default value if key is invalid
    *
    *  @remarks
    *    Only works if the type is a map (see isMap()).
    */
    Variant element(const std::string & key) const;

    /**
    *  @brief
    *    Set element of a map as variant
    *
    *  @param[in] key
    *    Key
    *  @param[in] value
    *    Value of element
    *
    *  @remarks
    *    Only works if the type is a map (see isMap()).
    */
    void setElement(const std::string & key, const Variant & value);


protected:
    std::unique_ptr<AbstractValueContainer> m_value; ///< Stored value (can be null)
};


} // namespace cppexpose


#include <cppexpose/variant/Variant.inl>
