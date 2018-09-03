
#pragma once
#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <typename RET, typename... Arguments>
StaticFunction<RET, Arguments...>::StaticFunction(Func func)
: m_func(func)
{
}

template <typename RET, typename... Arguments>
StaticFunction<RET, Arguments...>::~StaticFunction()
{
}

template <typename RET, typename... Arguments>
std::unique_ptr<AbstractFunction> StaticFunction<RET, Arguments...>::clone()
{
    return cppassist::make_unique<StaticFunction<RET, Arguments...>>(m_func);
}

template <typename RET, typename... Arguments>
Variant StaticFunction<RET, Arguments...>::call(const std::vector<Variant> & args)
{
    return callFunction(typename helper::GenSeq<sizeof...(Arguments)>::Type(), args);
}

template <typename RET, typename... Arguments>
template<size_t... I>
Variant StaticFunction<RET, Arguments...>::callFunction(helper::Seq<I...>, const std::vector<Variant> & args)
{
    return helper::CallFunction<RET, Arguments...>::call(m_func, helper::ArgValueGen<I, Arguments...>::Type::get(args)...);
}


} // namespace cppexpose
