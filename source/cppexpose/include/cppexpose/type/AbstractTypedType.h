
#pragma once


#include <cppexpose/type/AbstractType.h>


namespace cppexpose
{


template <typename T>
class Type;


/**
*  @brief
*    Abstract base class for types
*/
template <typename T, typename ET>
class CPPEXPOSE_TEMPLATE_API AbstractTypedType : public AbstractType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractTypedType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractTypedType();

    // Virtual AbstractType interface
    virtual const AbstractType & elementType() const override;

    // Default value
    virtual const T & defaultValue() const = 0;

    // Conversion to basic types
    virtual std::string toString(const T & var) const = 0;
    virtual bool fromString(T & var, const std::string & value) const = 0;
    virtual bool toBool(const T & var) const = 0;
    virtual bool fromBool(T & var, bool value) const = 0;
    virtual long long toLongLong(const T & var) const = 0;
    virtual bool fromLongLong(T & var, long long value) const = 0;
    virtual unsigned long long toULongLong(const T & var) const = 0;
    virtual bool fromULongLong(T & var, unsigned long long value) const = 0;
    virtual double toDouble(const T & var) const = 0;
    virtual bool fromDouble(T & var, double value) const = 0;

    // Array interface
    virtual size_t numElements(const T & var) const = 0;
    virtual ET getElement(const T & var, size_t i) const = 0;
    virtual void setElement(T & var, size_t i, ET value) const = 0;
    virtual void push(T & var, ET value) const = 0;

    // Map interface
    virtual std::vector<std::string> keys(const T & var) const = 0;
    virtual ET getElement(const T & var, const std::string & key) const = 0;
    virtual void setElement(T & var, const std::string & key, ET value) const = 0;
};


} // namespace cppexpose


#include <cppexpose/type/AbstractTypedType.inl>
