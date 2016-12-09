
#pragma once


namespace cppexpose
{


template <typename Type>
TypedComponent<Type>::TypedComponent(
    const std::string & name
  , const std::string & description
  , const std::string & type
  , const std::string & tags
  , const std::string & icon
  , const std::string & annotations
  , const std::string & vendor
  , const std::string & version)
: AbstractComponent(name, description, type, tags, icon, annotations, vendor, version)
{
}

template <typename Type>
TypedComponent<Type>::~TypedComponent()
{
}


} // namespace cppexpose
