
#pragma once


#include <cppassist/memory/make_unique.h>


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100) // 'identifier': unreferenced formal parameter
#endif


namespace cppexpose
{


template <class T, typename RET, typename... Arguments>
MemberFunction<T, RET, Arguments...>::MemberFunction(T * obj, Func func)
: m_obj(obj)
, m_func(func)
{
}

template <class T, typename RET, typename... Arguments>
MemberFunction<T, RET, Arguments...>::~MemberFunction()
{
}

template <class T, typename RET, typename... Arguments>
std::unique_ptr<AbstractFunction> MemberFunction<T, RET, Arguments...>::clone()
{
    return cppassist::make_unique<MemberFunction<T, RET, Arguments...>>(m_obj, m_func);
}

template <class T, typename RET, typename... Arguments>
Variant MemberFunction<T, RET, Arguments...>::call(const std::vector<Variant> & args)
{
    return this->callMethod(typename helper::GenSeq<sizeof...(Arguments)>::Type(), args);
}

template <class T, typename RET, typename... Arguments>
template<size_t... I>
Variant MemberFunction<T, RET, Arguments...>::callMethod(helper::Seq<I...>, const std::vector<Variant> & args)
{
    return helper::CallMethod<T, RET, Arguments...>::call(m_obj, m_func, helper::ArgValueGen<I, Arguments...>::Type::get(args)...);
}


} // namespace cppexpose


#ifdef _MSC_VER
#pragma warning(pop)
#endif
