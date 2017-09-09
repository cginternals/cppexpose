
#pragma once


#include <memory>

#include <cppexpose/type/AbstractTyped.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class for containers that hold a typed value
*/
class CPPEXPOSE_API AbstractValueContainer : public AbstractTyped
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractValueContainer();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractValueContainer();

    /**
    *  @brief
    *    Check if value can be converted to a specific type
    *
    *  @return
    *    'true' if value can be converted into type ValueType, else 'false'.
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
    *    Get value and convert it
    *
    *  @return
    *    Value converted into ValueType, or defaultValue if type does not match and cannot be converted
    */
    template <typename ValueType>
    ValueType value() const;

    /**
    *  @brief
    *    Create copy of the value
    *
    *  @return
    *    Typed value
    */
    virtual std::unique_ptr<AbstractValueContainer> createCopy() const = 0;

    /**
    *  @brief
    *    Convert value into string
    *
    *  @return
    *    Converted value
    */
    virtual std::string toString() const = 0;

    /**
    *  @brief
    *    Set value from string
    *
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromString(const std::string & value) = 0;

    /**
    *  @brief
    *    Convert value into boolean
    *
    *  @return
    *    Converted value
    */
    virtual bool toBool() const = 0;

    /**
    *  @brief
    *    Set value from boolean
    *
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromBool(bool value) = 0;

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
    *    Set value from long long
    *
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromLongLong(long long value) = 0;

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
    *    Set value from unsigned long long
    *
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromULongLong(unsigned long long value) = 0;

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
    *    Set value from double
    *
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromDouble(double value) = 0;
};


} // namespace cppexpose


#include <cppexpose/value/AbstractValueContainer.inl>
