
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/Function.h>
#include <cppexpose/StaticFunction.h>
#include <cppexpose/MemberFunction.h>
#include <cppexpose/ConstMemberFunction.h>


namespace cppexpose
{


template <typename Type, typename... Args>
bool Object::createProperty(const std::string & name, Args&&... args)
{
    auto value = cppassist::make_unique<Var<Type>>(std::forward<Args>(args)...);
    return addProperty(name, std::move(value));
}

template <typename RetType, typename... Args>
void Object::addFunction(const std::string & name, RetType (*fn)(Args...))
{
    auto func = cppassist::make_unique<StaticFunction<RetType, Args...>>(fn);
    this->createProperty<Function>(name, Function(std::move(func)));
}

template <class Type, typename RetType, typename... Args>
void Object::addFunction(const std::string & name, Type * obj, RetType (Type::*fn)(Args...))
{
    auto func = cppassist::make_unique<MemberFunction<Type, RetType, Args...>>(obj, fn);
    this->createProperty<Function>(name, Function(std::move(func)));
}

template <class Type, typename RetType, typename... Args>
void Object::addFunction(const std::string & name, Type * obj, RetType (Type::*fn)(Args...) const)
{
    auto func = cppassist::make_unique<ConstMemberFunction<Type, RetType, Args...>>(obj, fn);
    this->createProperty<Function>(name, Function(std::move(func)));
}

template <typename Type, typename... Args>
bool Object::createSignal(const std::string & name, Args&&... args)
{
    auto signal = cppassist::make_unique<Signal<Args...>>();
    return addSignal(name, std::move(signal));
}


} // namespace cppexpose
