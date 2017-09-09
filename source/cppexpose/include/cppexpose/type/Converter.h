
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractValueContainer;


/**
*  @brief
*    Class template for type conversions
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API Converter
{
    /**
    *  @brief
    *    Check if an AbstractValueContainer can be converted into type T
    *
    *  @return
    *    'true' if value can be converted, else 'false'
    */
    static bool canConvert();

    /**
    *  @brief
    *    Convert AbstractValueContainer into type T
    *
    *  @param[in] value
    *    Typed value
    *
    *  @return
    *    Converted value
    */
    static T convertTo(const cppexpose::AbstractValueContainer & value);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to bool
*/
template <>
struct CPPEXPOSE_API Converter<bool>
{
    static bool canConvert();
    static bool convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to char
*/
template <>
struct CPPEXPOSE_API Converter<char>
{
    static bool canConvert();
    static char convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to unsigned char
*/
template <>
struct CPPEXPOSE_API Converter<unsigned char>
{
    static bool canConvert();
    static unsigned char convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to short
*/
template <>
struct CPPEXPOSE_API Converter<short>
{
    static bool canConvert();
    static short convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to unsigned short
*/
template <>
struct CPPEXPOSE_API Converter<unsigned short>
{
    static bool canConvert();
    static unsigned short convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to int
*/
template <>
struct CPPEXPOSE_API Converter<int>
{
    static bool canConvert();
    static int convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to unsigned int
*/
template <>
struct CPPEXPOSE_API Converter<unsigned int>
{
    static bool canConvert();
    static unsigned int convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to long
*/
template <>
struct CPPEXPOSE_API Converter<long>
{
    static bool canConvert();
    static long convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to unsigned long
*/
template <>
struct CPPEXPOSE_API Converter<unsigned long>
{
    static bool canConvert();
    static unsigned long convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to long long
*/
template <>
struct CPPEXPOSE_API Converter<long long>
{
    static bool canConvert();
    static long long convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to unsigned long long
*/
template <>
struct CPPEXPOSE_API Converter<unsigned long long>
{
    static bool canConvert();
    static unsigned long long convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to float
*/
template <>
struct CPPEXPOSE_API Converter<float>
{
    static bool canConvert();
    static float convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to double
*/
template <>
struct CPPEXPOSE_API Converter<double>
{
    static bool canConvert();
    static double convertTo(const cppexpose::AbstractValueContainer &);
};

/**
*  @brief
*    Converter specialization from AbstractValueContainer to std::string
*/
template <>
struct CPPEXPOSE_API Converter<std::string>
{
    static bool canConvert();
    static std::string convertTo(const cppexpose::AbstractValueContainer &);
};


} // namespace cppexpose


#include <cppexpose/type/Converter.inl>
