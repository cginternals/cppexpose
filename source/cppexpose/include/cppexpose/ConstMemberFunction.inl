
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <class Type, typename ReturnType, typename... Arguments>
ConstMemberFunction<Type, ReturnType, Arguments...>::ConstMemberFunction(const Type * obj, Func func)
: m_obj(obj)
, m_func(func)
{
}

template <class Type, typename ReturnType, typename... Arguments>
ConstMemberFunction<Type, ReturnType, Arguments...>::~ConstMemberFunction()
{
}

template <class Type, typename ReturnType, typename... Arguments>
std::unique_ptr<AbstractFunction> ConstMemberFunction<Type, ReturnType, Arguments...>::clone()
{
    return cppassist::make_unique<ConstMemberFunction<Type, ReturnType, Arguments...>>(m_obj, m_func);
}

template <class Type, typename ReturnType, typename... Arguments>
Variant ConstMemberFunction<Type, ReturnType, Arguments...>::call(const std::vector<Variant> & args)
{
    return this->callMethod(typename helper::GenSeq<sizeof...(Arguments)>::Type(), args);
}

template <class Type, typename ReturnType, typename... Arguments>
template<size_t... I>
Variant ConstMemberFunction<Type, ReturnType, Arguments...>::callMethod(helper::Seq<I...>, const std::vector<Variant> & args)
{
    return helper::CallConstMethod<Type, ReturnType, Arguments...>::call(m_obj, m_func, helper::ArgValueGen<I, Arguments...>::Type::get(args)...);
}


} // namespace cppexpose
