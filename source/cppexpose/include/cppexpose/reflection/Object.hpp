
#pragma once


#include <cppexpose/reflection/Object.h>

#include <cppexpose/function/StaticFunction.h>
#include <cppexpose/function/MemberFunction.h>


namespace cppexpose
{


template <typename RET, typename... Arguments>
void Object::addFunction(const std::string & name, RET (*fn)(Arguments...))
{
    AbstractFunction * func = new StaticFunction<RET, Arguments...>(fn);
    m_functions.push_back(Function(name, func));
}

template <class T, typename RET, typename... Arguments>
void Object::addFunction(const std::string & name, T * obj, RET (T::*fn)(Arguments...))
{
    AbstractFunction * func = new MemberFunction<T, RET, Arguments...>(obj, fn);
    m_functions.push_back(Function(name, func));
}


} // namespace cppexpose
