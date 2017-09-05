
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
class CPPEXPOSE_TEMPLATE_API EnumValues
{
public:
    /**
    *  @brief
    *    Get symbolic names and their values
    *
    *  @return
    *    Map of symbolic names and values
    */
    static std::map<std::string, T> namedValues();
};


} // namespace cppexpose


#include <cppexpose/type/EnumValues.inl>
