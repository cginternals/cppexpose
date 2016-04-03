
#pragma once


#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of an enum value
*/
template <typename T>
class TypedEnum : public Typed<T>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedEnum();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedEnum();

    // Virtual Typed<T> interface
    virtual std::string typeName() const override;
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & value) override;
    virtual bool toBool() const override;
    virtual bool fromBool(bool value) override;
    virtual long long toLongLong() const override;
    virtual bool fromLongLong(long long value) override;
    virtual unsigned long long toULongLong() const override;
    virtual bool fromULongLong(unsigned long long value) override;
    virtual double toDouble() const override;
    virtual bool fromDouble(double value) override;
};


} // namespace cppexpose


#include <cppexpose/typed/TypedEnum.hpp>
