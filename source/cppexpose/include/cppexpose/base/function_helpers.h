
#pragma once


#include <functional>
#include <string>
#include <vector>

#include <cppexpose/variant/Variant.h>


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
*    Template for parsing typed arguments from a list of variants
*/
template<typename T, size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue {
    static int get(const std::vector<Variant> & args) {
        // Assume signed integral type by default
        int value = 0;
        if (POS < args.size()) {
            value = args[POS].value<int>();
        }
        return value;
    }
};

template<typename T, size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<const T &, POS> {
    static T get(const std::vector<Variant> & args) {
        return ArgValue<T, POS>::get(args);
    }
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<float, POS> {
    static float get(const std::vector<Variant> & args) {
        float value = 0.0f;
        if (POS < args.size()) {
            value = (float)args[POS].value<double>();
        }
        return value;
    }
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<double, POS> {
    static double get(const std::vector<Variant> & args) {
        double value = 0.0f;
        if (POS < args.size()) {
            value = args[POS].value<double>();
        }
        return value;
    }
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<bool, POS> {
    static bool get(const std::vector<Variant> & args) {
        bool value = false;
        if (POS < args.size()) {
            value = args[POS].value<bool>();
        }
        return value;
    }
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<std::string, POS> {
    static std::string get(const std::vector<Variant> & args) {
        std::string value;
        if (POS < args.size()) {
            value = args[POS].value<std::string>();
        }
        return value;
    }
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<Variant, POS> {
    static Variant get(const std::vector<Variant> & args) {
        Variant value;
        if (POS < args.size()) {
            value = args[POS];
        }
        return value;
    }
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<const Variant &, POS> {
    static Variant get(const std::vector<Variant> & args) {
        return ArgValue<Variant, POS>::get(args);
    }
};

template<typename T, size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<const std::vector<T> &, POS> {
    static std::vector<T> get(const std::vector<Variant> & args) {
        if (POS < args.size()) {
            return args[POS].toVector<T>();
        } else {
            return std::vector<T>();
        }
    }
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<const std::vector<Variant> &, POS> {
    static std::vector<Variant> get(const std::vector<Variant> & args) {
        std::vector<Variant> list;
        for (size_t i=POS; i<args.size(); i++) {
            list.push_back(args[i]);
        }
        return list;
    }
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<cppexpose::Object *, POS> {
    static cppexpose::Object * get(const std::vector<Variant> & args) {
        cppexpose::Object * obj = nullptr;
        if (POS < args.size()) {
            obj = args[POS].value<cppexpose::Object *>();
        }
        return obj;
    }
};

template<size_t POS>
struct CPPEXPOSE_TEMPLATE_API ArgValue<const cppexpose::Object *, POS> {
    static const cppexpose::Object * get(const std::vector<Variant> & args) {
        return ArgValue<cppexpose::Object *, POS>::get(args);
    }
};


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
struct CPPEXPOSE_TEMPLATE_API GenSeq<0, I...> { typedef Seq<I...> Type; };

/**
*  @brief
*    Pick type by index (e.g., PickType<1, void, int, float>::Type = int)
*/
template<size_t N, typename T, typename... Arguments>
struct CPPEXPOSE_TEMPLATE_API PickType : PickType<N-1, Arguments...> {};

template<typename T, typename... Arguments>
struct CPPEXPOSE_TEMPLATE_API PickType<0, T, Arguments...> { typedef T Type; };

/**
*  @brief
*    Generate ArgValue class for types and index (e.g., ArgValueGen<2, float, int, double>::Type = ArgValue<int, 2>
*/
template<size_t I, typename... Arguments>
struct CPPEXPOSE_TEMPLATE_API ArgValueGen
{
    typedef typename PickType<I, Arguments...>::Type T;
    typedef ArgValue<T, I>                           Type;
};

/**
*  @brief
*    Template for calling a static function with a return value
*/
template <typename RET, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallFunction
{
public:
    typedef std::function<RET (Arguments...)> FuncPtr;

    static Variant call(FuncPtr func, Arguments... args) {
        return Variant( func(args...) );
    }
};

/**
*  @brief
*    Template for calling a static function without a return value
*/
template <typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallFunction<void, Arguments...>
{
public:
    typedef std::function<void (Arguments...)> FuncPtr;

    static Variant call(FuncPtr func, Arguments... args) {
        func(args...);
        return Variant();
    }
};

/**
*  @brief
*    Template for calling a member function with a return value
*/
template <typename T, typename RET, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallMethod
{
public:
    typedef RET (T::*MethodPtr) (Arguments...);

    static Variant call(T * obj, MethodPtr method, Arguments... args) {
        return Variant((obj->*method)(args...));
    }
};

/**
*  @brief
*    Template for calling a member function without a return value
*/
template <typename T, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallMethod<T, void, Arguments...>
{
public:
    typedef void (T::*MethodPtr) (Arguments...);

    static Variant call(T * obj, MethodPtr method, Arguments... args) {
        (obj->*method)(args...);
        return Variant();
    }
};

/**
*  @brief
*    Template for calling a const member function with a return value
*/
template <typename T, typename RET, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallConstMethod
{
public:
    typedef RET (T::*MethodPtr) (Arguments...) const;

    static Variant call(const T * obj, MethodPtr method, Arguments... args) {
        return Variant((obj->*method)(args...));
    }
};

/**
*  @brief
*    Template for calling a const member function without a return value
*/
template <typename T, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallConstMethod<T, void, Arguments...>
{
public:
    typedef void (T::*MethodPtr) (Arguments...) const;

    static Variant call(const T * obj, MethodPtr method, Arguments... args) {
        (obj->*method)(args...);
        return Variant();
    }
};


} // namespace helper


} // namespace cppexpose
