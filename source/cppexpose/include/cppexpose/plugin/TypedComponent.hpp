
#pragma once


#include <cppexpose/plugin/TypedComponent.h>


namespace cppexpose
{


template <typename Type>
TypedComponent<Type>::TypedComponent(
    const std::string & name
  , const std::string & description
  , const std::string & type
  , const std::string & subtype
  , const std::string & annotations
  , const std::string & vendor
  , const std::string & version)
: AbstractComponent(name, description, type, subtype, annotations, vendor, version)
{
}

template <typename Type>
TypedComponent<Type>::~TypedComponent()
{
}


} // namespace cppexpose
