
#pragma once


#include <cppexpose/base/template_helpers.h>

#include <cppexpose/typed/TypedGeneric.hh>
#include <cppexpose/typed/TypedBool.hh>
#include <cppexpose/typed/TypedString.hh>
#include <cppexpose/typed/TypedSignedIntegral.hh>
#include <cppexpose/typed/TypedUnsignedIntegral.hh>
#include <cppexpose/typed/TypedFloatingPoint.hh>
#include <cppexpose/typed/TypedEnum.hh>
#include <cppexpose/typed/TypedArray.hh>
#include <cppexpose/typed/TypedVariant.hh>


namespace cppexpose
{


/**
*  @brief
*    Helper class for selecting types
*
*    Specialize this class template to register a new type.
*    Define the typed class that you want to use as typedef Type.
*/
template <typename T, typename = void>
struct TypeSelector
{
    using Type = TypedGeneric<T>;
};

/**
*  @brief
*    Type selector for bool
*/
template <>
struct TypeSelector<bool>
{
    using Type = TypedBool<bool>;
};

/**
*  @brief
*    Type selector for const bool
*/
template <>
struct TypeSelector<const bool>
{
    using Type = TypedBool<const bool>;
};

/**
*  @brief
*    Type selector for std::string
*/
template <>
struct TypeSelector<std::string>
{
    using Type = TypedString<std::string>;
};

/**
*  @brief
*    Type selector for const std::string
*/
template <>
struct TypeSelector<const std::string>
{
    using Type = TypedString<const std::string>;
};

/**
*  @brief
*    Type selector for signed integral types
*/
template <typename T>
struct TypeSelector<T, helper::EnableIf<helper::isSignedIntegral<T>>>
{
    using Type = TypedSignedIntegral<T>;
};

/**
*  @brief
*    Type selector for unsigned integral types
*/
template <typename T>
struct TypeSelector<T, helper::EnableIf<helper::isUnsignedIntegral<T>>>
{
    using Type = TypedUnsignedIntegral<T>;
};

/**
*  @brief
*    Type selector for floating point types
*/
template <typename T>
struct TypeSelector<T, helper::EnableIf<helper::isFloatingPoint<T>>>
{
    using Type = TypedFloatingPoint<T>;
};

/**
*  @brief
*    Type selector for enum types
*/
template <typename T>
struct TypeSelector<T, helper::EnableIf<std::is_enum<T>>>
{
    using Type = TypedEnum<T>;
};

/**
*  @brief
*    Type selector for array types
*/
template <typename T>
struct TypeSelector<T, helper::EnableIf<helper::isArray<T>>>
{
    using Type = TypedArray<T, typename T::value_type, std::tuple_size<T>::value>;
};

/**
*  @brief
*    Type selector for cppexpose::Variant
*/
template <>
struct TypeSelector<cppexpose::Variant>
{
    using Type = TypedVariant<cppexpose::Variant>;
};

/**
*  @brief
*    Type selector for const cppexpose::Variant
*/
template <>
struct TypeSelector<const cppexpose::Variant>
{
    using Type = TypedVariant<const cppexpose::Variant>;
};


} // namespace cppexpose
