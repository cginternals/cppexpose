
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
template <typename T, typename BASE, typename = void>
struct TypeSelector
{
    using Type = TypedGeneric<T, BASE>;
};

/**
*  @brief
*    Type selector for bool
*/
template <typename BASE>
struct TypeSelector<bool, BASE>
{
    using Type = TypedBool<bool, BASE>;
};

/**
*  @brief
*    Type selector for const bool
*/
template <typename BASE>
struct TypeSelector<const bool, BASE>
{
    using Type = TypedBool<const bool, BASE>;
};

/**
*  @brief
*    Type selector for std::string
*/
template <typename BASE>
struct TypeSelector<std::string, BASE>
{
    using Type = TypedString<std::string, BASE>;
};

/**
*  @brief
*    Type selector for const std::string
*/
template <typename BASE>
struct TypeSelector<const std::string, BASE>
{
    using Type = TypedString<const std::string, BASE>;
};

/**
*  @brief
*    Type selector for signed integral types
*/
template <typename T, typename BASE>
struct TypeSelector<T, BASE, helper::EnableIf<helper::isSignedIntegral<T>>>
{
    using Type = TypedSignedIntegral<T, BASE>;
};

/**
*  @brief
*    Type selector for unsigned integral types
*/
template <typename T, typename BASE>
struct TypeSelector<T, BASE, helper::EnableIf<helper::isUnsignedIntegral<T>>>
{
    using Type = TypedUnsignedIntegral<T, BASE>;
};

/**
*  @brief
*    Type selector for floating point types
*/
template <typename T, typename BASE>
struct TypeSelector<T, BASE, helper::EnableIf<helper::isFloatingPoint<T>>>
{
    using Type = TypedFloatingPoint<T, BASE>;
};

/**
*  @brief
*    Type selector for enum types
*/
template <typename T, typename BASE>
struct TypeSelector<T, BASE, helper::EnableIf<std::is_enum<T>>>
{
    using Type = TypedEnum<T, BASE>;
};

/**
*  @brief
*    Type selector for array types
*/
template <typename T, typename BASE>
struct TypeSelector<T, BASE, helper::EnableIf<helper::isArray<T>>>
{
    using Type = TypedArray<T, typename T::value_type, std::tuple_size<T>::value, BASE>;
};

/**
*  @brief
*    Type selector for cppexpose::Variant
*/
template <typename BASE>
struct TypeSelector<cppexpose::Variant, BASE>
{
    using Type = TypedVariant<cppexpose::Variant, BASE>;
};

/**
*  @brief
*    Type selector for const cppexpose::Variant
*/
template <typename BASE>
struct TypeSelector<const cppexpose::Variant, BASE>
{
    using Type = TypedVariant<const cppexpose::Variant, BASE>;
};


} // namespace cppexpose
