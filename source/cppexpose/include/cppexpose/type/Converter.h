
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractValue;


template <typename T>
struct CPPEXPOSE_TEMPLATE_API Converter
{
    static bool canConvert();
    static T convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<bool>
{
    static bool canConvert();
    static bool convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<char>
{
    static bool canConvert();
    static char convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<unsigned char>
{
    static bool canConvert();
    static unsigned char convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<short>
{
    static bool canConvert();
    static short convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<unsigned short>
{
    static bool canConvert();
    static unsigned short convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<int>
{
    static bool canConvert();
    static int convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<unsigned int>
{
    static bool canConvert();
    static unsigned int convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<long>
{
    static bool canConvert();
    static long convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<unsigned long>
{
    static bool canConvert();
    static unsigned long convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<long long>
{
    static bool canConvert();
    static long long convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<unsigned long long>
{
    static bool canConvert();
    static unsigned long long convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<float>
{
    static bool canConvert();
    static float convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<double>
{
    static bool canConvert();
    static double convertTo(const cppexpose::AbstractValue &);
};

template <>
struct CPPEXPOSE_API Converter<std::string>
{
    static bool canConvert();
    static std::string convertTo(const cppexpose::AbstractValue &);
};


} // namespace cppexpose


#include <cppexpose/type/Converter.inl>
