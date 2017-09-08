
#pragma once


#include <cppassist/memory/make_unique.h>

#include <cppexpose/type/BaseType.h>


namespace cppexpose
{


template <typename T>
Type Type::basicType()
{
    Type type;
    type.m_type = cppassist::make_unique<BaseType<T>>();

    return type;
}


} // namespace cppexpose
