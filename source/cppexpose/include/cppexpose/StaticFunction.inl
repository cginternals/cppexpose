
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <typename ReturnType, typename... Arguments>
StaticFunction<ReturnType, Arguments...>::StaticFunction(Func func)
: m_func(func)
{
}

template <typename ReturnType, typename... Arguments>
StaticFunction<ReturnType, Arguments...>::~StaticFunction()
{
}

template <typename ReturnType, typename... Arguments>
std::unique_ptr<AbstractFunction> StaticFunction<ReturnType, Arguments...>::clone()
{
    return cppassist::make_unique<StaticFunction<ReturnType, Arguments...>>(m_func);
}

template <typename ReturnType, typename... Arguments>
Variant StaticFunction<ReturnType, Arguments...>::call(const std::vector<Variant> & args)
{
    return callFunction(typename helper::GenSeq<sizeof...(Arguments)>::Type(), args);
}

template <typename ReturnType, typename... Arguments>
template<size_t... I>
Variant StaticFunction<ReturnType, Arguments...>::callFunction(helper::Seq<I...>, const std::vector<Variant> & args)
{
    return helper::CallFunction<ReturnType, Arguments...>::call(m_func, helper::ArgValueGen<I, Arguments...>::Type::get(args)...);
}


} // namespace cppexpose
