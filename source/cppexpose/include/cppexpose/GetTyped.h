
#pragma once


#include <cppassist/fs/FilePath.h>

#include <cppexpose/template_helpers.h>
#include <cppexpose/Function.hh>
#include <cppexpose/TypedGeneric.hh>
#include <cppexpose/TypedBool.hh>
#include <cppexpose/TypedString.hh>
#include <cppexpose/TypedSignedIntegral.hh>
#include <cppexpose/TypedUnsignedIntegral.hh>
#include <cppexpose/TypedFloatingPoint.hh>
#include <cppexpose/TypedEnum.hh>
#include <cppexpose/TypedPointer.hh>
#include <cppexpose/TypedObjectPointer.hh>
#include <cppexpose/TypedArrayPointer.hh>
#include <cppexpose/TypedArray.hh>
#include <cppexpose/TypedFunction.hh>
//#include <cppexpose/TypedFilePath.hh>


namespace cppexpose
{


/**
*  @brief
*    Get appropriate Typed<> class for given data type
*
*    Specialize this class template to register a new type.
*    Define the typed class that you want to use as typedef Type.
*/
template <typename Type, typename = void>
struct CPPEXPOSE_TEMPLATE_API GetTyped
{
    using VarType = TypedGeneric<Type>;
};

/**
*  @brief
*    Type selector for bool
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<bool>
{
    using VarType = TypedBool<bool>;
};

/**
*  @brief
*    Type selector for const bool
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const bool>
{
    using VarType = TypedBool<const bool>;
};

/**
*  @brief
*    Type selector for std::string
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<std::string>
{
    using VarType = TypedString<std::string>;
};

/**
*  @brief
*    Type selector for const std::string
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const std::string>
{
    using VarType = TypedString<const std::string>;
};

/**
*  @brief
*    Type selector for signed integral types
*/
template <typename Type>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, helper::EnableIf<helper::isSignedIntegral<Type>>>
{
    using VarType = TypedSignedIntegral<Type>;
};

/**
*  @brief
*    Type selector for unsigned integral types
*/
template <typename Type>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, helper::EnableIf<helper::isUnsignedIntegral<Type>>>
{
    using VarType = TypedUnsignedIntegral<Type>;
};

/**
*  @brief
*    Type selector for floating point types
*/
template <typename Type>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, helper::EnableIf<helper::isFloatingPoint<Type>>>
{
    using VarType = TypedFloatingPoint<Type>;
};

/**
*  @brief
*    Type selector for enum types
*/
template <typename Type>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, helper::EnableIf<std::is_enum<Type>>>
{
    using VarType = TypedEnum<Type>;
};

/**
*  @brief
*    Type selector for pointer types
*/
template <typename Type>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, helper::EnableIf<std::is_pointer<Type>>>
{
    using VarType = TypedPointer<Type>;
};

/**
*  @brief
*    Type selector for pointer to Object
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<cppexpose::Object *>
{
    using VarType = TypedObjectPointer<cppexpose::Object *>;
};

/**
*  @brief
*    Type selector for pointer to Object (const)
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const cppexpose::Object *>
{
    using VarType = TypedObjectPointer<const cppexpose::Object *>;
};

/**
*  @brief
*    Type selector for pointer to Array
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<cppexpose::Array *>
{
    using VarType = TypedArrayPointer<cppexpose::Array *>;
};

/**
*  @brief
*    Type selector for pointer to Array (const)
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const cppexpose::Array *>
{
    using VarType = TypedArrayPointer<const cppexpose::Array *>;
};

/**
*  @brief
*    Type selector for array types
*/
template <typename Type>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Type, helper::EnableIf<helper::isArray<Type>>>
{
    using VarType = TypedArray<Type>;
};

/**
*  @brief
*    Type selector for Object
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<cppexpose::Object>
{
    using VarType = cppexpose::Object;
};

/**
*  @brief
*    Type selector for Object (const)
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const cppexpose::Object>
{
    using VarType = cppexpose::Object;
};

/**
*  @brief
*    Type selector for Array
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<cppexpose::Array>
{
    using VarType = cppexpose::Array;
};

/**
*  @brief
*    Type selector for Array (const)
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const cppexpose::Array>
{
    using VarType = cppexpose::Array;
};

/**
*  @brief
*    Type selector for Variant
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<cppexpose::Variant>
{
    using VarType = cppexpose::Variant;
};

/**
*  @brief
*    Type selector for Variant (const)
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const cppexpose::Variant>
{
    using VarType = cppexpose::Variant;
};

/**
*  @brief
*    Type selector for functions
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<Function>
{
    using VarType = TypedFunction<Function>;
};

/**
*  @brief
*    Type selector for cppassist::FilePath
*/
/*
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<cppassist::FilePath>
{
    using VarType = TypedFilePath<cppassist::FilePath>;
};
*/

/**
*  @brief
*    Type selector for const cppassist::FilePath
*/
/*
template <>
struct CPPEXPOSE_TEMPLATE_API GetTyped<const cppassist::FilePath>
{
    using VarType = TypedFilePath<const cppassist::FilePath>;
};
*/


} // namespace cppexpose
