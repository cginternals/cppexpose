
#pragma once


#include <string>
#include <vector>
#include <map>

#include <cppexpose/cppexpose_api.h>
#include <cppexpose/typed/Typed.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of an enum value
*/
template <typename T, typename BASE>
class CPPEXPOSE_TEMPLATE_API TypedEnum : public Typed<T, BASE>
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
    void setStrings(const std::map<T, std::string> & pairs);

    // Virtual Typed<T> interface
    virtual std::string typeName() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool fromVariant(const Variant & variant) override;
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


protected:
    std::map<T, std::string> m_stringMap;
    std::map<std::string, T> m_enumMap;
};


/**
*  @brief
*    Default value mapping for enum type
*
*    Specialize this template to provide a default string mapping for an enum.
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API EnumDefaultStrings
{
    /**
    *  @brief
    *    Return available enum values and their string representations
    *
    *  @return
    *    Map of values and strings
    */
    std::map<T, std::string> operator()();
};


} // namespace cppexpose
