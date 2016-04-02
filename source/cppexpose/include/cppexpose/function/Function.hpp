
#pragma once


#include <cppexpose/function/Function.h>


namespace cppexpose
{


template <typename RET, typename... Arguments>
Function<RET, Arguments...>::Function(const std::string & name, FuncPtr func)
: AbstractFunction(name)
, m_func(func)
{
}

template <typename RET, typename... Arguments>
Function<RET, Arguments...>::~Function()
{
}

template <typename RET, typename... Arguments>
AbstractFunction * Function<RET, Arguments...>::clone()
{
    return new Function<RET, Arguments...>(m_name, m_func);
}

template <typename RET, typename... Arguments>
Variant Function<RET, Arguments...>::call(const std::vector<Variant> & args)
{
    return callFunction(typename helper::GenSeq<sizeof...(Arguments)>::Type(), args);
}

template <typename RET, typename... Arguments>
template<size_t... I>
Variant Function<RET, Arguments...>::callFunction(helper::Seq<I...>, const std::vector<Variant> & args)
{
    return helper::CallFunction<RET, Arguments...>::call(m_func, helper::ArgValueGen<I, Arguments...>::Type::get(args)...);
}


} // namespace cppexpose
