
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/function/StaticFunction.h>
#include <cppexpose/function/MemberFunction.h>


namespace cppexpose
{


template <typename T>
DynamicProperty<T> * Object::createDynamicProperty(const std::string & name, const T & value)
{
    // Reject properties that have no name or whose name already exists
    if (name == "" || this->propertyExists(name))
    {
        return nullptr;
    }

    // Create property and add it to the object
    auto property = cppassist::make_unique<DynamicProperty<T>>(name, nullptr, value);
    auto propertyPtr = property.get();
    this->addProperty(std::move(property));

    // Return property
    return propertyPtr;
}

template <typename RET, typename... Arguments>
void Object::addFunction(const std::string & name, RET (*fn)(Arguments...))
{
    AbstractFunction * func = new StaticFunction<RET, Arguments...>(fn);
    m_functions.push_back(Method(name, func));
}

template <class T, typename RET, typename... Arguments>
void Object::addFunction(const std::string & name, T * obj, RET (T::*fn)(Arguments...))
{
    auto func = cppassist::make_unique<MemberFunction<T, RET, Arguments...>>(obj, fn);
    m_functions.push_back(Method(name, std::move(func)));
}


} // namespace cppexpose
