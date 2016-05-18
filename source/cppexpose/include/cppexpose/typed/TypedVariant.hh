
#pragma once


#include <cppexpose/typed/Typed.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a variant value
*/
template <typename T, typename BASE>
class TypedVariant : public Typed<T, BASE>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedVariant();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedVariant();

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
    virtual bool isVariant() const override;
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
