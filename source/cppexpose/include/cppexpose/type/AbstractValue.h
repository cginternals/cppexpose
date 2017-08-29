
#pragma once


#include <cppexpose/type/IType.h>


namespace cppexpose
{


class AbstractType;


/**
*  @brief
*    Abstract base class for values
*/
class CPPEXPOSE_API AbstractValue : public IType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractValue();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractValue();

    /**
    *  @brief
    *    Get type of the stored value
    *
    *  @return
    *    Type object
    */
    virtual const AbstractType & type() const = 0;

    // Basic type conversions
    virtual std::string toString() const = 0;
    virtual bool fromString(const std::string & value) = 0;
    virtual bool toBool() const = 0;
    virtual bool fromBool(bool value) = 0;
    virtual long long toLongLong() const = 0;
    virtual bool fromLongLong(long long value) = 0;
    virtual unsigned long long toULongLong() const = 0;
    virtual bool fromULongLong(unsigned long long value) = 0;
    virtual double toDouble() const = 0;
    virtual bool fromDouble(double value) = 0;

    // Conversions
    template <typename T>
    bool canConvert() const;

    template <typename T>
    T value() const;
};


} // namespace cppexpose


#include <cppexpose/type/AbstractValue.inl>
