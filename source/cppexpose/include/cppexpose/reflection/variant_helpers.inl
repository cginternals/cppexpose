
#pragma once


#include <cppexpose/base/function_helpers.h>

#include <cppexpose/reflection/Variant.hh>


namespace cppexpose
{


namespace helper
{


template<typename T, size_t POS>
int ArgValue<T, POS>::get(const std::vector<Variant> & args)
{
    // Assume signed integral type by default
    int value = 0;
    if (POS < args.size()) {
        value = args[POS].value<int>();
    }
    return value;
}

template<typename T, size_t POS>
T ArgValue<const T &, POS>::get(const std::vector<Variant> & args)
{
    return ArgValue<T, POS>::get(args);
}

template<size_t POS>
float ArgValue<float, POS>::get(const std::vector<Variant> & args)
{
    float value = 0.0f;
    if (POS < args.size()) {
        value = (float)args[POS].value<double>();
    }
    return value;
}

template<size_t POS>
double ArgValue<double, POS>::get(const std::vector<Variant> & args)
{
    double value = 0.0f;
    if (POS < args.size()) {
        value = args[POS].value<double>();
    }
    return value;
}

template<size_t POS>
bool ArgValue<bool, POS>::get(const std::vector<Variant> & args)
{
    bool value = false;
    if (POS < args.size()) {
        value = args[POS].value<bool>();
    }
    return value;
}

template<size_t POS>
std::string ArgValue<std::string, POS>::get(const std::vector<Variant> & args)
{
    std::string value;
    if (POS < args.size()) {
        value = args[POS].value<std::string>();
    }
    return value;
}

template<size_t POS>
Variant ArgValue<Variant, POS>::get(const std::vector<Variant> & args)
{
    Variant value;
    if (POS < args.size()) {
        value = args[POS];
    }
    return value;
}

template<size_t POS>
Variant ArgValue<const Variant &, POS>::get(const std::vector<Variant> & args)
{
    return ArgValue<Variant, POS>::get(args);
}

template<size_t POS>
std::vector<Variant> ArgValue<const std::vector<Variant> &, POS>::get(const std::vector<Variant> & args)
{
    std::vector<Variant> list;
    for (size_t i=POS; i<args.size(); i++) {
        list.push_back(args[i]);
    }
    return list;
}

template<size_t POS>
cppexpose::Object * ArgValue<cppexpose::Object *, POS>::get(const std::vector<Variant> & args) {
    cppexpose::Object * obj = nullptr;
    if (POS < args.size()) {
        obj = args[POS].value<cppexpose::Object *>();
    }
    return obj;
}

template<size_t POS>
const cppexpose::Object * ArgValue<const cppexpose::Object *, POS>::get(const std::vector<Variant> & args)
{
    return ArgValue<cppexpose::Object *, POS>::get(args);
}

template <typename RET, typename... Arguments>
Variant CallFunction<RET, Arguments...>::call(FuncPtr func, Arguments... args)
{
    return Variant( func(args...) );
}

template <typename... Arguments>
Variant CallFunction<void, Arguments...>::call(FuncPtr func, Arguments... args)
{
    func(args...);
    return Variant();
}

template <typename T, typename RET, typename... Arguments>
Variant CallMethod<T, RET, Arguments...>::call(T * obj, MethodPtr method, Arguments... args)
{
    return Variant((obj->*method)(args...));
}

template <typename T, typename... Arguments>
Variant CallMethod<T, void, Arguments...>::call(T * obj, MethodPtr method, Arguments... args)
{
    (obj->*method)(args...);
    return Variant();
}

template <typename T, typename RET, typename... Arguments>
Variant CallConstMethod<T, RET, Arguments...>::call(const T * obj, MethodPtr method, Arguments... args)
{
    return Variant((obj->*method)(args...));
}

template <typename T, typename... Arguments>
Variant CallConstMethod<T, void, Arguments...>::call(const T * obj, MethodPtr method, Arguments... args)
{
    (obj->*method)(args...);
    return Variant();
}


} // namespace helper


} // namespace cppexpose
