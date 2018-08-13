
#pragma once


#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for number types
*/
template <typename Type, typename Storage>
class CPPEXPOSE_TEMPLATE_API AbstractNumber : public Storage
{
public:
    /**
    *  @brief
    *    Constructor with default value
    *
    *  @param[in] defaultValue
    *    Default value (used if no initial value is given in args)
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    AbstractNumber(Type defaultValue, Args&&... args);

    /**
    *  @brief
    *    Constructor with initial value
    *
    *  @param[in] defaultValue
    *    Default value (used if no initial value is given in args)
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    AbstractNumber(Type defaultValue, Type value, Args&&... args);

    /**
    *  @brief
    *    Constructor with initial value and value range
    *
    *  @param[in] defaultValue
    *    Default value (used if no initial value is given in args)
    *  @param[in] minValue
    *    Minimum value
    *  @param[in] maxValue
    *    Maximum value
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    AbstractNumber(Type defaultValue, Type value, Type minValue, Type maxValue, Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractNumber();

    // Replication
    virtual std::unique_ptr<AbstractVar> clone() const override;

    // Variable type
    virtual VarType type() const override;
    virtual bool isNull() const override;
    virtual bool isBool() const override;
    virtual bool isNumber() const override;
    // virtual bool isIntegral() const = 0;
    // virtual bool isSignedIntegral() const = 0;
    // virtual bool isFloatingPoint() const = 0;
    virtual bool isEnum() const override;
    virtual bool isString() const override;
    virtual bool isExternal() const override;
    virtual bool isPointer() const override;
    virtual bool isObject() const override;
    virtual bool isArray() const override;
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
    //   Overloaded in derived classes

    // Direct access
    virtual const Object * asObject() const override;
    virtual const Array * asArray() const override;

protected:
    Type m_minValue; ///< Minimum value
    Type m_maxValue; ///< Minimum value
};


} // namespace cppexpose


#include <cppexpose/AbstractNumber.inl>
