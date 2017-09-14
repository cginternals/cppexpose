
#pragma once


#include <cppexpose/reflection/Variant.hh>
#include <cppexpose/reflection/Object.hh>


namespace cppexpose
{


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
*    Template for calling a static function with a return value
*/
template <typename RET, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API CallFunction
{
public:
    using FuncPtr = std::function<RET (Arguments...)>;

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
    using FuncPtr = std::function<void (Arguments...)>;

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
    using MethodPtr = RET (T::*) (Arguments...);

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
    using MethodPtr = void (T::*) (Arguments...);

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
    using MethodPtr = RET (T::*) (Arguments...) const;

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
    using MethodPtr = void (T::*) (Arguments...) const;

    static Variant call(const T * obj, MethodPtr method, Arguments... args) {
        (obj->*method)(args...);
        return Variant();
    }
};


} // namespace helper


}// namespace cppexpose
