
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/reflection/Property.h>

#include <cppexpose/function/StaticFunction.h>
#include <cppexpose/function/MemberFunction.h>
#include <cppexpose/function/ConstMemberFunction.h>


namespace cppexpose
{


template <typename T>
Property<T> * Object::createDynamicProperty(const std::string & name, const T & value)
{
    // Reject properties that have no name or whose name already exists
    if (name == "" || this->propertyExists(name))
    {
        return nullptr;
    }

    // Create property and add it to the object
    auto property = cppassist::make_unique<Property<T>>(name, nullptr, value);
    auto propertyPtr = property.get();
    this->addProperty(std::move(property));

    // Return property
    return propertyPtr;
}

template <typename Type, typename ... Arguments>
bool Object::addProperty(const std::string & name, Arguments && ... arguments)
{
    auto property = cppassist::make_unique<Property<Type>>(name, nullptr, std::forward<Arguments>(arguments)...);
    return addProperty(std::move(property));
}

template <typename RET, typename... Arguments>
void Object::addFunction(const std::string & name, RET (*fn)(Arguments...))
{
    auto func = cppassist::make_unique<StaticFunction<RET, Arguments...>>(fn);
    m_functions.push_back(Method(name, std::move(func)));
}

template <class T, typename RET, typename... Arguments>
void Object::addFunction(const std::string & name, T * obj, RET (T::*fn)(Arguments...))
{
    auto func = cppassist::make_unique<MemberFunction<T, RET, Arguments...>>(obj, fn);
    m_functions.push_back(Method(name, std::move(func)));
}

template <class T, typename RET, typename... Arguments>
void Object::addFunction(const std::string & name, T * obj, RET (T::*fn)(Arguments...) const)
{
    auto func = cppassist::make_unique<ConstMemberFunction<T, RET, Arguments...>>(obj, fn);
    m_functions.push_back(Method(name, std::move(func)));
}


} // namespace cppexpose
