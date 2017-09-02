
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractValue;


/**
*  @brief
*    Class template for type conversions
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API Converter
{
    /**
    *  @brief
    *    Check if an AbstractValue can be converted into type T
    *
    *  @return
    *    'true' if value can be converted, else 'false'
    */
    static bool canConvert();

    /**
    *  @brief
    *    Convert AbstractValue into type T
    *
    *  @param[in] value
    *    Typed value
    *
    *  @return
    *    Converted value
    */
    static T convertTo(const cppexpose::AbstractValue & value);
};

/**
*  @brief
*    Converter specialization from AbstractValue to bool
*/
template <>
struct CPPEXPOSE_API Converter<bool>
{
    static bool canConvert();
    static bool convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to char
*/
template <>
struct CPPEXPOSE_API Converter<char>
{
    static bool canConvert();
    static char convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to unsigned char
*/
template <>
struct CPPEXPOSE_API Converter<unsigned char>
{
    static bool canConvert();
    static unsigned char convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to short
*/
template <>
struct CPPEXPOSE_API Converter<short>
{
    static bool canConvert();
    static short convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to unsigned short
*/
template <>
struct CPPEXPOSE_API Converter<unsigned short>
{
    static bool canConvert();
    static unsigned short convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to int
*/
template <>
struct CPPEXPOSE_API Converter<int>
{
    static bool canConvert();
    static int convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to unsigned int
*/
template <>
struct CPPEXPOSE_API Converter<unsigned int>
{
    static bool canConvert();
    static unsigned int convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to long
*/
template <>
struct CPPEXPOSE_API Converter<long>
{
    static bool canConvert();
    static long convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to unsigned long
*/
template <>
struct CPPEXPOSE_API Converter<unsigned long>
{
    static bool canConvert();
    static unsigned long convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to long long
*/
template <>
struct CPPEXPOSE_API Converter<long long>
{
    static bool canConvert();
    static long long convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to unsigned long long
*/
template <>
struct CPPEXPOSE_API Converter<unsigned long long>
{
    static bool canConvert();
    static unsigned long long convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to float
*/
template <>
struct CPPEXPOSE_API Converter<float>
{
    static bool canConvert();
    static float convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to double
*/
template <>
struct CPPEXPOSE_API Converter<double>
{
    static bool canConvert();
    static double convertTo(const cppexpose::AbstractValue &);
};

/**
*  @brief
*    Converter specialization from AbstractValue to std::string
*/
template <>
struct CPPEXPOSE_API Converter<std::string>
{
    static bool canConvert();
    static std::string convertTo(const cppexpose::AbstractValue &);
};


} // namespace cppexpose


#include <cppexpose/type/Converter.inl>
