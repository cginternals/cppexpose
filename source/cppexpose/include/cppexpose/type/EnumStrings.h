
#pragma once


#include <string>
#include <map>

#include <cppexpose/type/TypeSignedIntegral.h>


namespace cppexpose
{


/**
*  @brief
*    Default symbolic names for enum types
*
*    Specialize this template to provide the name and value mappings for an enum.
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API EnumStrings
{
public:
    /**
    *  @brief
    *    Get symbolic names and their values
    *
    *  @return
    *    Map of values and strings
    */
    static std::map<T, std::string> symbolicNames();
};


} // namespace cppexpose


#include <cppexpose/type/EnumStrings.inl>
