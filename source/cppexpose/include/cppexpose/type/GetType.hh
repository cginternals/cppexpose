
#pragma once


#include <type_traits>
#include <array>
#include <vector>
#include <map>

#include <cppexpose/base/template_helpers.h>
#include <cppexpose/type/NullType.hh>
#include <cppexpose/type/MetaType.hh>
#include <cppexpose/type/BaseTypeImplGeneric.hh>
#include <cppexpose/type/BaseTypeImplBool.hh>
#include <cppexpose/type/BaseTypeImplSignedIntegral.hh>
#include <cppexpose/type/BaseTypeImplUnsignedIntegral.hh>
#include <cppexpose/type/BaseTypeImplFloatingPoint.hh>
#include <cppexpose/type/BaseTypeImplString.hh>
#include <cppexpose/type/BaseTypeImplEnum.hh>
#include <cppexpose/type/BaseTypeImplArray.hh>
#include <cppexpose/type/BaseTypeImplVector.hh>
#include <cppexpose/type/BaseTypeImplMap.hh>
#include <cppexpose/type/BaseTypeImplPointer.hh>


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
    using Type = BaseTypeImplGeneric<T>;
};

/**
*  @brief
*    Type selector for void
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetType<void>
{
    using Type = NullType;
};

/**
*  @brief
*    Type selector for bool
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetType<bool>
{
    using Type = BaseTypeImplBool<bool>;
};

/**
*  @brief
*    Type selector for std::string
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetType<std::string>
{
    using Type = BaseTypeImplString<std::string>;
};

/**
*  @brief
*    Type selector for signed integral types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<helper::isSignedIntegral<T>>>
{
    using Type = BaseTypeImplSignedIntegral<T>;
};

/**
*  @brief
*    Type selector for unsigned integral types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<helper::isUnsignedIntegral<T>>>
{
    using Type = BaseTypeImplUnsignedIntegral<T>;
};

/**
*  @brief
*    Type selector for floating point types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<helper::isFloatingPoint<T>>>
{
    using Type = BaseTypeImplFloatingPoint<T>;
};

/**
*  @brief
*    Type selector for enum types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<std::is_enum<T>>>
{
    using Type = BaseTypeImplEnum<T>;
};

/**
*  @brief
*    Type selector for std::array types
*/
template <typename T, size_t SIZE>
struct CPPEXPOSE_TEMPLATE_API GetType<std::array<T, SIZE>>
{
    using Type = BaseTypeImplArray<std::array<T, SIZE>, T, SIZE>;
};

/**
*  @brief
*    Type selector for array types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T, helper::EnableIf<helper::isArray2<T>>>
{
    using Type = BaseTypeImplArray<T, typename std::remove_extent<T>::type, std::extent<T>::value>;
};

/**
*  @brief
*    Type selector for std::vector types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<std::vector<T>>
{
    using Type = BaseTypeImplVector<std::vector<T>, T>;
};

/**
*  @brief
*    Type selector for std::map types
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<std::map<std::string, T>>
{
    using Type = BaseTypeImplMap<std::map<std::string, T>, T>;
};

/**
*  @brief
*    Type selector for void pointer
*/
template <>
struct CPPEXPOSE_TEMPLATE_API GetType<void *>
{
    using Type = BaseTypeImplGeneric<void *>;
};

/**
*  @brief
*    Type selector for plain pointer types (int*, Object*, ...)
*/
template <typename T>
struct CPPEXPOSE_TEMPLATE_API GetType<T *>
{
    using Type = BaseTypeImplPointer<T *, T *>;
};


} // namespace cppexpose
