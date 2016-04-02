
#pragma once


#include <vector>
#include <array>
#include <type_traits>

#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


/**
*  @brief
*    Template helpers that deal with type traits and conditional template specialization.
*/
namespace helper
{


template <bool Condition, bool... MoreConditions>
struct all;

template <bool... MoreConditions>
struct all<true, MoreConditions...> : public all<MoreConditions...> {};

template <bool... MoreConditions>
struct all<false, MoreConditions...> : public std::false_type {};

template <>
struct all<true> : public std::true_type {};

template <bool Condition>
struct neg : public std::true_type {};

template <>
struct neg<true> : public std::false_type {};

template <typename Type>
struct is_array : public std::false_type {};

template <typename Type, size_t Size>
struct is_array<std::array<Type, Size>> : public std::true_type {};

template <typename Type, typename Container>
struct is_special_array : public std::false_type {};

template <typename Type, size_t Size>
struct is_special_array<Type, std::array<Type, Size>> : public std::true_type {};

template <typename Condition, typename Type>
struct value_accessor : public std::enable_if<Condition::value, Type> {};

/**
*  @brief
*    Used to choose specific property implementation for different types at compile time via SFINAE
*
*  @see http://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
*/
template <typename Condition, typename Type = void>
using EnableIf = typename value_accessor<Condition, Type>::type; 

template <typename Condition>
struct Neg : public neg<Condition::value> {};

template <bool... Conditions>
struct And : public all<Conditions...> {};

template <typename Type>
struct isArray : public is_array<Type> {};

template <typename Type>
struct isBoolArray : public is_special_array<bool, Type> {};

template <typename Type>
struct isIntArray : public is_special_array<int, Type> {};

template <typename Type>
struct isDoubleArray : public is_special_array<double, Type> {};

template <typename Type>
struct isIntegral : public And<std::is_integral<Type>::value, 
                               Neg<std::is_same<Type, bool>>::value> {};

template <typename Type>
struct isUnsignedIntegral : public And<std::is_integral<Type>::value, 
                                       std::is_unsigned<Type>::value, 
                                       Neg<std::is_same<Type, bool>>::value> {};

template <typename Type>
struct isSignedIntegral : public And<std::is_integral<Type>::value, 
                                     std::is_signed<Type>::value, 
                                     Neg<std::is_same<Type, bool>>::value> {};

template <typename Type>
struct isFloatingPoint : public And<std::is_floating_point<Type>::value,
                                    Neg<std::is_same<Type, long double>>::value> {};
                                    
template <typename Type>
struct isPlain : public And<Neg<std::is_reference<Type>>::value,
                            Neg<std::is_const<Type>>::value,
                            Neg<std::is_volatile<Type>>::value> {};


/**
*  @brief
*    Template for parsing typed arguments from a list of variants
*/
template<typename T, size_t POS>
struct ArgValue {
    static T get(const std::vector<Variant> & args) {
        // Assume signed integral type by default
        T value = 0;
        if (POS < args.size()) {
            value = args[POS].value<int>();
        }
        return value;
    }
};

template<typename T, size_t POS>
struct ArgValue<const T &, POS> {
    static T get(const std::vector<Variant> & args) {
        return ArgValue<T, POS>::get(args);
    }
};

template<size_t POS>
struct ArgValue<float, POS> {
    static float get(const std::vector<Variant> & args) {
        float value = 0.0f;
        if (POS < args.size()) {
            value = (float)args[POS].value<double>();
        }
        return value;
    }
};

template<size_t POS>
struct ArgValue<double, POS> {
    static double get(const std::vector<Variant> & args) {
        double value = 0.0f;
        if (POS < args.size()) {
            value = args[POS].value<double>();
        }
        return value;
    }
};

template<size_t POS>
struct ArgValue<bool, POS> {
    static bool get(const std::vector<Variant> & args) {
        bool value = false;
        if (POS < args.size()) {
            value = args[POS].value<bool>();
        }
        return value;
    }
};

template<size_t POS>
struct ArgValue<std::string, POS> {
    static std::string get(const std::vector<Variant> & args) {
        std::string value;
        if (POS < args.size()) {
            value = args[POS].value<std::string>();
        }
        return value;
    }
};

template<size_t POS>
struct ArgValue<Variant, POS> {
    static Variant get(const std::vector<Variant> & args) {
        Variant value;
        if (POS < args.size()) {
            value = args[POS];
        }
        return value;
    }
};

template<size_t POS>
struct ArgValue<const Variant &, POS> {
    static Variant get(const std::vector<Variant> & args) {
        return ArgValue<Variant, POS>::get(args);
    }
};

template<size_t POS>
struct ArgValue<const std::vector<Variant> &, POS> {
    static std::vector<Variant> get(const std::vector<Variant> & args) {
        std::vector<Variant> list;
        for (size_t i=POS; i<args.size(); i++) {
            list.push_back(args[i]);
        }
        return list;
    }
};

/**
*  @brief
*    Generate a sequence of numbers (e.g., Seq<0, 1, 2>)
*/
template<size_t... I>
struct Seq {};

/**
*  @brief
*    Sequence generator (e.g., GenSec<3>::Type = Seq<0, 1, 2>)
*/
template<int N, size_t... I>
struct GenSeq : GenSeq<N-1, N-1, I...> {};

template<size_t... I>
struct GenSeq<0, I...> { typedef Seq<I...> Type; };

/**
*  @brief
*    Pick type by index (e.g., PickType<1, void, int, float>::Type = int)
*/
template<size_t N, typename T, typename... Arguments>
struct PickType : PickType<N-1, Arguments...> {};

template<typename T, typename... Arguments>
struct PickType<0, T, Arguments...> { typedef T Type; };

/**
*  @brief
*    Generate ArgValue class for types and index (e.g., ArgValueGen<2, float, int, double>::Type = ArgValue<int, 2>
*/
template<size_t I, typename... Arguments>
struct ArgValueGen {
    typedef typename PickType<I, Arguments...>::Type T;
    typedef ArgValue<T, I>                           Type;
};

/**
*  @brief
*    Template for calling a static function with a return value
*/
template <typename RET, typename... Arguments>
class CallFunction
{
public:
    typedef RET (*FuncPtr) (Arguments...);

    static Variant call(FuncPtr func, Arguments... args) {
        return Variant( (*func)(args...) );
    }
};

/**
*  @brief
*    Template for calling a static function without a return value
*/
template <typename... Arguments>
class CallFunction<void, Arguments...>
{
public:
    typedef void (*FuncPtr) (Arguments...);

    static Variant call(FuncPtr func, Arguments... args) {
        (*func)(args...);
        return Variant();
    }
};

/**
*  @brief
*    Template for calling a member function with a return value
*/
template <typename T, typename RET, typename... Arguments>
class CallMethod
{
public:
    typedef RET (T::*MethodPtr) (Arguments...);

    static Variant call(T * obj, MethodPtr method, Arguments... args) {
        return Variant( (obj->*method)(args...) );
    }
};

/**
*  @brief
*    Template for calling a member function without a return value
*/
template <typename T, typename... Arguments>
class CallMethod<T, void, Arguments...>
{
public:
    typedef void (T::*MethodPtr) (Arguments...);

    static Variant call(T * obj, MethodPtr method, Arguments... args) {
        (obj->*method)(args...);
        return Variant();
    }
};


} // namespace helper


} // namespace cppexpose
