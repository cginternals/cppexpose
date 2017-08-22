
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


template <class T, typename RET, typename... Arguments>
ConstMemberFunction<T, RET, Arguments...>::ConstMemberFunction(const T * obj, Func func)
: m_obj(obj)
, m_func(func)
{
}

template <class T, typename RET, typename... Arguments>
ConstMemberFunction<T, RET, Arguments...>::~ConstMemberFunction()
{
}

template <class T, typename RET, typename... Arguments>
std::unique_ptr<AbstractFunction> ConstMemberFunction<T, RET, Arguments...>::clone()
{
    return cppassist::make_unique<ConstMemberFunction<T, RET, Arguments...>>(m_obj, m_func);
}

template <class T, typename RET, typename... Arguments>
Variant ConstMemberFunction<T, RET, Arguments...>::call(const std::vector<Variant> & args)
{
    return this->callMethod(typename helper::GenSeq<sizeof...(Arguments)>::Type(), args);
}

template <class T, typename RET, typename... Arguments>
template<size_t... I>
Variant ConstMemberFunction<T, RET, Arguments...>::callMethod(helper::Seq<I...>, const std::vector<Variant> & args)
{
    return helper::CallConstMethod<T, RET, Arguments...>::call(m_obj, m_func, helper::ArgValueGen<I, Arguments...>::Type::get(args)...);
}


} // namespace cppexpose
