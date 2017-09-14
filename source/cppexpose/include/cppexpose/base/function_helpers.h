
#pragma once


#include <vector>
#include <type_traits>
#include <functional>


namespace cppexpose
{


class Object;


/**
*  @brief
*    Template helpers that deal with type traits and conditional template specialization.
*/
namespace helper
{


/**
*  @brief
*    Generate a sequence of numbers (e.g., Seq<0, 1, 2>)
*/
template<size_t... I>
struct CPPEXPOSE_TEMPLATE_API Seq {};

/**
*  @brief
*    Sequence generator (e.g., GenSec<3>::Type = Seq<0, 1, 2>)
*/
template<int N, size_t... I>
struct CPPEXPOSE_TEMPLATE_API GenSeq : GenSeq<N-1, N-1, I...> {};

template<size_t... I>
struct CPPEXPOSE_TEMPLATE_API GenSeq<0, I...> { using Type = Seq<I...>; };

/**
*  @brief
*    Pick type by index (e.g., PickType<1, void, int, float>::Type = int)
*/
template<size_t N, typename T, typename... Arguments>
struct CPPEXPOSE_TEMPLATE_API PickType : PickType<N-1, Arguments...> {};

template<typename T, typename... Arguments>
struct CPPEXPOSE_TEMPLATE_API PickType<0, T, Arguments...> { using Type = T; };

/**
*  @brief
*    Generate ArgValue class for types and index (e.g., ArgValueGen<2, float, int, double>::Type = ArgValue<int, 2>
*/
template<size_t I, typename... Arguments>
struct CPPEXPOSE_TEMPLATE_API ArgValueGen
{
    using T    = typename PickType<I, Arguments...>::Type;
    using Type = ArgValue<T, I>;
};


} // namespace helper


} // namespace cppexpose
