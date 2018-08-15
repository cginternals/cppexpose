
#pragma once


#include <cppassist/fs/FilePath.h>

#include <cppexpose/template_helpers.h>
#include <cppexpose/TypedGeneric.h>
#include <cppexpose/TypedBool.h>
#include <cppexpose/TypedString.h>
#include <cppexpose/TypedSignedIntegral.h>
#include <cppexpose/TypedUnsignedIntegral.h>
#include <cppexpose/TypedFloatingPoint.h>
#include <cppexpose/TypedEnum.h>
#include <cppexpose/TypedPointer.h>
#include <cppexpose/TypedArray.h>
//#include <cppexpose/TypedVariant.h>
//#include <cppexpose/TypedFilePath.h>


namespace cppexpose
{


/**
*  @brief
*    Get appropriate Typed<> class for given data type
*
*    Specialize this class template to register a new type.
*    Define the typed class that you want to use as typedef Type.
*/
template <typename Type, typename Storage, typename = void>
struct CPPEXPOSE_TEMPLATE_API GetTyped
{
    using VarType = TypedGeneric<Type, Storage>;
};

/**
*  @brief
*    Type selector for bool
*/
template <typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<bool, Storage>
{
    using VarType = TypedBool<bool, Storage>;
};

/**
*  @brief
*    Type selector for const bool
*/
template <typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const bool, Storage>
{
    using VarType = TypedBool<const bool, Storage>;
};

/**
*  @brief
*    Type selector for std::string
*/
template <typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<std::string, Storage>
{
    using VarType = TypedString<std::string, Storage>;
};

/**
*  @brief
*    Type selector for const std::string
*/
template <typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const std::string, Storage>
{
    using VarType = TypedString<const std::string, Storage>;
};

/**
*  @brief
*    Type selector for signed integral types
*/
template <typename Type, typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, Storage, helper::EnableIf<helper::isSignedIntegral<Type>>>
{
    using VarType = TypedSignedIntegral<Type, Storage>;
};

/**
*  @brief
*    Type selector for unsigned integral types
*/
template <typename Type, typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, Storage, helper::EnableIf<helper::isUnsignedIntegral<Type>>>
{
    using VarType = TypedUnsignedIntegral<Type, Storage>;
};

/**
*  @brief
*    Type selector for floating point types
*/
template <typename Type, typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, Storage, helper::EnableIf<helper::isFloatingPoint<Type>>>
{
    using VarType = TypedFloatingPoint<Type, Storage>;
};

/**
*  @brief
*    Type selector for enum types
*/
template <typename Type, typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, Storage, helper::EnableIf<std::is_enum<Type>>>
{
    using VarType = TypedEnum<Type, Storage>;
};

/**
*  @brief
*    Type selector for pointer types
*/
template <typename Type, typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, Storage, helper::EnableIf<std::is_pointer<Type>>>
{
    using VarType = TypedPointer<Type, Storage>;
};

/**
*  @brief
*    Type selector for array types
*/
template <typename Type, typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, Storage, helper::EnableIf<helper::isArray<Type>>>
{
    using VarType = TypedArray<Type, Storage>;
};

/**
*  @brief
*    Type selector for cppexpose::Variant
*/
/*
template <typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<cppexpose::Variant, Storage>
{
    using VarType = TypedVariant<cppexpose::Variant, Storage>;
};
*/

/**
*  @brief
*    Type selector for const cppexpose::Variant
*/
/*
template <typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const cppexpose::Variant, Storage>
{
    using VarType = TypedVariant<const cppexpose::Variant, Storage>;
};
*/

/**
*  @brief
*    Type selector for cppassist::FilePath
*/
/*
template <typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<cppassist::FilePath, Storage>
{
    using VarType = TypedFilePath<cppassist::FilePath, Storage>;
};
*/

/**
*  @brief
*    Type selector for const cppassist::FilePath
*/
/*
template <typename Storage>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const cppassist::FilePath, Storage>
{
    using VarType = TypedFilePath<const cppassist::FilePath, Storage>;
};
*/


} // namespace cppexpose
