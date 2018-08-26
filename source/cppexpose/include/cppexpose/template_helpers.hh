
#pragma once


#include <array>
#include <type_traits>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Template helpers that deal with type traits and conditional template specialization.
*/
namespace helper
{


template <bool Condition, bool... MoreConditions>
struct CPPEXPOSE_TEMPLATE_API all;

template <bool... MoreConditions>
struct CPPEXPOSE_TEMPLATE_API all<true, MoreConditions...> : public all<MoreConditions...> {};

template <bool... MoreConditions>
struct CPPEXPOSE_TEMPLATE_API all<false, MoreConditions...> : public std::false_type {};

template <>
struct CPPEXPOSE_TEMPLATE_API all<true> : public std::true_type {};

template <bool Condition>
struct CPPEXPOSE_TEMPLATE_API neg : public std::true_type {};

template <>
struct CPPEXPOSE_TEMPLATE_API neg<true> : public std::false_type {};

template <typename Type>
struct CPPEXPOSE_TEMPLATE_API is_array : public std::false_type {};

template <typename Type, size_t Size>
struct CPPEXPOSE_TEMPLATE_API is_array<std::array<Type, Size>> : public std::true_type {};

template <typename Type, typename Container>
struct CPPEXPOSE_TEMPLATE_API is_special_array : public std::false_type {};

template <typename Type, size_t Size>
struct CPPEXPOSE_TEMPLATE_API is_special_array<Type, std::array<Type, Size>> : public std::true_type {};

template <typename Condition, typename Type>
struct CPPEXPOSE_TEMPLATE_API value_accessor : public std::enable_if<Condition::value, Type> {};

/**
*  @brief
*    Used to choose specific property implementation for different types at compile time via SFINAE
*
*  @see http://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
*/
template <typename Condition, typename Type = void>
using EnableIf = typename value_accessor<Condition, Type>::type; 

template <typename Condition>
struct CPPEXPOSE_TEMPLATE_API Neg : public neg<Condition::value> {};

template <bool... Conditions>
struct CPPEXPOSE_TEMPLATE_API And : public all<Conditions...> {};

template <typename Type>
struct CPPEXPOSE_TEMPLATE_API isArray : public is_array<Type> {};

template <typename Type>
struct CPPEXPOSE_TEMPLATE_API isBoolArray : public is_special_array<bool, Type> {};

template <typename Type>
struct CPPEXPOSE_TEMPLATE_API isIntArray : public is_special_array<int, Type> {};

template <typename Type>
struct CPPEXPOSE_TEMPLATE_API isDoubleArray : public is_special_array<double, Type> {};

template <typename Type>
struct CPPEXPOSE_TEMPLATE_API isIntegral : public And<std::is_integral<Type>::value,
                               Neg<std::is_same<Type, bool>>::value> {};

template <typename Type>
struct CPPEXPOSE_TEMPLATE_API isUnsignedIntegral : public And<std::is_integral<Type>::value,
                                       std::is_unsigned<Type>::value, 
                                       Neg<std::is_same<Type, bool>>::value> {};

template <typename Type>
struct CPPEXPOSE_TEMPLATE_API isSignedIntegral : public And<std::is_integral<Type>::value,
                                     std::is_signed<Type>::value, 
                                     Neg<std::is_same<Type, bool>>::value> {};

template <typename Type>
struct CPPEXPOSE_TEMPLATE_API isFloatingPoint : public And<std::is_floating_point<Type>::value,
                                    Neg<std::is_same<Type, long double>>::value> {};
                                    
template <typename Type>
struct CPPEXPOSE_TEMPLATE_API isPlain : public And<Neg<std::is_reference<Type>>::value,
                            Neg<std::is_const<Type>>::value,
                            Neg<std::is_volatile<Type>>::value> {};


} // namespace helper


} // namespace cppexpose
