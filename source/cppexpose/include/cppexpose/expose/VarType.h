
#pragma once


#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Type of a variable
*/
enum class VarType : unsigned int
{
    Null = 0, ///< Empty type
    Bool,     ///< Boolean
    Number,   ///< Number (integer or floating point)
    Enum,     ///< Named constant (enum)
    String,   ///< String
    External, ///< External type (e.g., an exported C++ class)
    Pointer,  ///< Pointer type
    Object,   ///< Instance of Object
    Array,    ///< Instance of Array
    Function  ///< Callable function
};


} // namespace cppexpose
