
#pragma once


#include <cppexpose/base/string_helpers.h>

#include <sstream>


namespace cppexpose
{

namespace string_helpers
{


template <typename Type>
Type fromString(const std::string & string)
{
    std::stringstream stream(string);
    auto value = typename std::remove_const<Type>::type();
    stream >> value;
    return value;
}

template <typename Type>
std::string toString(const Type & value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}


} // namespace string_helpers
    
} // namespace cppexpose
