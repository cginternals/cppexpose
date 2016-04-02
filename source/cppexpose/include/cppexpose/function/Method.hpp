
#pragma once


#include <cppexpose/function/Method.h>


namespace cppexpose
{


template <class T, typename RET, typename... Arguments>
Method<T, RET, Arguments...>::Method(const std::string & name, T * obj, MethodPtr method)
: AbstractFunction(name)
, m_method(method)
, m_obj(obj)
{
}

template <class T, typename RET, typename... Arguments>
Method<T, RET, Arguments...>::~Method()
{
}

template <class T, typename RET, typename... Arguments>
AbstractFunction * Method<T, RET, Arguments...>::clone()
{
    return new Method<T, RET, Arguments...>(m_name, m_obj, m_method);
}

template <class T, typename RET, typename... Arguments>
Variant Method<T, RET, Arguments...>::call(const std::vector<Variant> & args)
{
    return callMethod(typename helper::GenSeq<sizeof...(Arguments)>::Type(), args);
}

template <class T, typename RET, typename... Arguments>
template<size_t... I>
Variant Method<T, RET, Arguments...>::callMethod(helper::Seq<I...>, const std::vector<Variant> & args)
{
    return helper::CallMethod<T, RET, Arguments...>::call(m_obj, m_method, helper::ArgValueGen<I, Arguments...>::Type::get(args)...);
}


} // namespace cppexpose
