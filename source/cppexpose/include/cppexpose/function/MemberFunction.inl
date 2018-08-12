
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <class Type, typename ReturnType, typename... Arguments>
MemberFunction<Type, ReturnType, Arguments...>::MemberFunction(Type * obj, Func func)
: m_obj(obj)
, m_func(func)
{
}

template <class Type, typename ReturnType, typename... Arguments>
MemberFunction<Type, ReturnType, Arguments...>::~MemberFunction()
{
}

template <class Type, typename ReturnType, typename... Arguments>
std::unique_ptr<AbstractFunction> MemberFunction<Type, ReturnType, Arguments...>::clone()
{
    return cppassist::make_unique<MemberFunction<Type, ReturnType, Arguments...>>(m_obj, m_func);
}

template <class Type, typename ReturnType, typename... Arguments>
Variant MemberFunction<Type, ReturnType, Arguments...>::call(const std::vector<Variant> & args)
{
    return this->callMethod(typename helper::GenSeq<sizeof...(Arguments)>::Type(), args);
}

template <class Type, typename ReturnType, typename... Arguments>
template<size_t... I>
Variant MemberFunction<Type, ReturnType, Arguments...>::callMethod(helper::Seq<I...>, const std::vector<Variant> & args)
{
    return helper::CallMethod<Type, ReturnType, Arguments...>::call(m_obj, m_func, helper::ArgValueGen<I, Arguments...>::Type::get(args)...);
}


} // namespace cppexpose
