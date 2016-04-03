
#pragma once


#include <vector>
#include <string>
#include <functional>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{

namespace string_helpers
{


//@{
/**
*  @brief
*    Convert from std::string to Type
*
*  @param[in] string
*    String representation
*
*  @return
*    Primitive type value
*/
template <typename Type>
Type fromString(const std::string & string);

template <>
CPPEXPOSE_API char fromString<char>(const std::string & string);

template <>
CPPEXPOSE_API unsigned char fromString<unsigned char>(const std::string & string);
//@}

//@{
/**
*  @brief
*    Convert from Type to std::string
*
*  @param[in] value
*    Primitive type value
*
*  @return
*    String representation
*/
template <typename Type>
std::string toString(const Type & value);

template <>
CPPEXPOSE_API std::string toString<char>(const char & value);

template <>
CPPEXPOSE_API std::string toString<unsigned char>(const unsigned char & value);
//@}


//@{
/**
*  @brief
*    Trim string by removing whitespace
*
*  @param[in] string
*    String
*  @param[in] removeAllWhitespace
*    'true': remove whitespace everywhere in the string, 'false': remove whitespace at the beginning and the end of the string
*
*  @return
*    String
*/
CPPEXPOSE_API std::string trim(const std::string & string, bool removeAllWhitespace);
//@}

//@{
/**
*  @brief
*    Split string into substrings
*
*  @param[in] size
*    Number of elements
*  @param[in] string
*    Input string of the form "(<value>,<value>,<value>...)"
*
*  @return
*    List of strings
*/
CPPEXPOSE_API std::vector<std::string> parseArray(const std::string & string, size_t size);
//@}


} // namespace string_helpers

} // namespace cppexpose


#include <cppexpose/base/string_helpers.hpp>
