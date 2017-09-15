
#pragma once


#include <cppexpose/base/function_helpers.h>

#include <cppexpose/reflection/Variant.hh>


namespace cppexpose
{


namespace helper
{


/**
*  @brief
*    Template for parsing typed arguments from a list of variants
*/
template<typename T, size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue
{
    static int get(const std::vector<Variant> & args);
};

template<typename T, size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<const T &, POS>
{
    static T get(const std::vector<Variant> & args);
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<float, POS>
{
    static float get(const std::vector<Variant> & args);
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<double, POS>
{
    static double get(const std::vector<Variant> & args);
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<bool, POS>
{
    static bool get(const std::vector<Variant> & args);
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<std::string, POS>
{
    static std::string get(const std::vector<Variant> & args);
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<Variant, POS>
{
    static Variant get(const std::vector<Variant> & args);
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<const Variant &, POS>
{
    static Variant get(const std::vector<Variant> & args);
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<const std::vector<Variant> &, POS>
{
    static std::vector<Variant> get(const std::vector<Variant> & args);
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<cppexpose::Object *, POS>
{
    static cppexpose::Object * get(const std::vector<Variant> & args);
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<const cppexpose::Object *, POS>
{
    static const cppexpose::Object * get(const std::vector<Variant> & args);
};


/**
*  @brief
*    Template for calling a static function with a return value
*/
template <typename RET, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallFunction
{
public:
    using FuncPtr = std::function<RET (Arguments...)>;

    static Variant call(FuncPtr func, Arguments... args);
};

/**
*  @brief
*    Template for calling a static function without a return value
*/
template <typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallFunction<void, Arguments...>
{
public:
    using FuncPtr = std::function<void (Arguments...)>;

    static Variant call(FuncPtr func, Arguments... args);
};

/**
*  @brief
*    Template for calling a member function with a return value
*/
template <typename T, typename RET, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallMethod
{
public:
    using MethodPtr = RET (T::*) (Arguments...);

    static Variant call(T * obj, MethodPtr method, Arguments... args);
};

/**
*  @brief
*    Template for calling a member function without a return value
*/
template <typename T, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallMethod<T, void, Arguments...>
{
public:
    using MethodPtr = void (T::*) (Arguments...);

    static Variant call(T * obj, MethodPtr method, Arguments... args);
};

/**
*  @brief
*    Template for calling a const member function with a return value
*/
template <typename T, typename RET, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallConstMethod
{
public:
    using MethodPtr = RET (T::*) (Arguments...) const;

    static Variant call(const T * obj, MethodPtr method, Arguments... args);
};

/**
*  @brief
*    Template for calling a const member function without a return value
*/
template <typename T, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallConstMethod<T, void, Arguments...>
{
public:
    using MethodPtr = void (T::*) (Arguments...) const;

    static Variant call(const T * obj, MethodPtr method, Arguments... args);
};

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
