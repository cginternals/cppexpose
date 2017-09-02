
#pragma once


#include <type_traits>
#include <array>
#include <vector>
#include <map>

#include <cppexpose/base/template_helpers.h>
#include <cppexpose/type/TypeNull.h>
#include <cppexpose/type/TypeGeneric.h>
#include <cppexpose/type/TypeBoolean.h>
#include <cppexpose/type/TypeSignedIntegral.h>
#include <cppexpose/type/TypeUnsignedIntegral.h>
#include <cppexpose/type/TypeFloatingPoint.h>
#include <cppexpose/type/TypeString.h>
#include <cppexpose/type/TypeEnum.h>
#include <cppexpose/type/TypeArray.h>
#include <cppexpose/type/TypeVector.h>
#include <cppexpose/type/TypeMap.h>


namespace cppexpose
{


/**
*  @brief
*    Get appropriate Typed<> class for given data type
*
*    Specialize this class template to register a new type.
*    Define the typed class that you want to use as typedef Type.
*/
template <typename T, typename = void>
struct CPPEXPOSE_TEMPLATE_API GetType
{
    using Type = TypeGeneric<T>;
};

/**
*  @brief
*    Type selector for void
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetType<void>
{
    using Type = TypeNull;
};

/**
*  @brief
*    Type selector for bool
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetType<bool>
{
    using Type = TypeBoolean<bool>;
};

/**
*  @brief
*    Type selector for std::string
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetType<std::string>
{
    using Type = TypeString<std::string>;
};

/**
*  @brief
*    Type selector for signed integral types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<helper::isSignedIntegral<T>>>
{
    using Type = TypeSignedIntegral<T>;
};

/**
*  @brief
*    Type selector for unsigned integral types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<helper::isUnsignedIntegral<T>>>
{
    using Type = TypeUnsignedIntegral<T>;
};

/**
*  @brief
*    Type selector for floating point types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<helper::isFloatingPoint<T>>>
{
    using Type = TypeFloatingPoint<T>;
};

/**
*  @brief
*    Type selector for enum types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<std::is_enum<T>>>
{
    using Type = TypeEnum<T>;
};

/**
*  @brief
*    Type selector for std::array types
*/
template <typename T, size_t SIZE>
struct CPPEXPOSE_TEMPLATE_API GetType<std::array<T, SIZE>>
{
    using Type = TypeArray<std::array<T, SIZE>, T, SIZE>;
};

/**
*  @brief
*    Type selector for array types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<helper::isArray2<T>>>
{
    using Type = TypeArray<T, typename std::remove_extent<T>::type, std::extent<T>::value>;
};

/**
*  @brief
*    Type selector for std::vector types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<std::vector<T>>
{
    using Type = TypeVector<std::vector<T>, T>;
};

/**
*  @brief
*    Type selector for std::map types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<std::map<std::string, T>>
{
    using Type = TypeMap<std::map<std::string, T>, T>;
};


} // namespace cppexpose
