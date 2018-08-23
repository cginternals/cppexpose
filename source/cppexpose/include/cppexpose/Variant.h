
#pragma once


#include <memory>
#include <vector>

#include <cppexpose/AbstractVar.h>


namespace cppexpose
{


/**
*  @brief
*    Variable containing an arbitrarily typed value
*
*    A Variant can be used to store and pass arbitrary typed values in a uniform manner.
*
*    To create a Variant from a supported primitive data types, use one of the
*    available constructors. To create a Variant from another data type, use the
*    static function fromValue().
*
*    The type of the stored value can be determined by hasType<Type>().
*    To access the value of a variant, call convert<Type>(). If the given data type does not
*    match the stored type, the value may be converted. Note that this only works, if the
*    corresponding type class (see Typed* classes) has implemented an approriate conversion
*    to one of the primitive data types, and a conversion path between the two values can
*    be found. To check if a type can be converted, use canConvert<Type>().
*
*    To create object hierarchies, as analog to the JSON or javascript data models, use
*    the classes Object and Array, which can also be stored in a variant.
*/
class CPPEXPOSE_API Variant : public AbstractVar
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
    template <typename Type>
    static Variant fromValue(const Type & value);
    //@}


public:
    //@{
    /**
    *  @brief
    *    Constructor
    */
    Variant();

    /**
    *  @brief
    *    Copy Constructor
    *
    *  @param[in] variant
    *    Variant whose value will be copied
    */
    Variant(const Variant & variant);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Value that will be copied
    */
    Variant(const AbstractVar & value);

    /**
    *  @brief
    *    Move Constructor
    *
    *  @param[in] variant
    *    Variant whose value will be moved
    */
    Variant(Variant && variant);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Value that will be moved
    */
    Variant(AbstractVar && value);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Value that will be moved
    */
    Variant(std::unique_ptr<AbstractVar> && value);
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
    //@}

    //@{
    /**
    *  @brief
    *    Destructor
    */
    virtual ~Variant();

    /**
    *  @brief
    *    Assignment operator
    *
    *  @param[in] value
    *    Variant value that is copied
    */
    Variant & operator =(const Variant & value);

    /**
    *  @brief
    *    Move operator
    *
    *  @param[in] value
    *    Variant value that is moved
    */
    Variant & operator =(std::unique_ptr<AbstractVar> && value);
    //@}

    // Replication
    virtual std::unique_ptr<AbstractVar> clone() const override;
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

    // Direct access
    virtual const Object * asObject() const override;
    virtual const Array * asArray() const override;

protected:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] var
    *    Internal typed value
    *
    *  @remarks
    *    This constructor takes ownership over the given typed value
    *    and stored it in the variant.
    */
    Variant(AbstractVar * var);

protected:
    std::unique_ptr<AbstractVar> m_value;
};


} // namespace cppexpose


#include <cppexpose/Variant.inl>
