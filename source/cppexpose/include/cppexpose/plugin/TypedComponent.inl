
#pragma once


namespace cppexpose
{


template <typename Type, typename Enable>
TypedComponent<Type, Enable>::TypedComponent(
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

template <typename Type, typename Enable>
TypedComponent<Type, Enable>::~TypedComponent()
{
}


} // namespace cppexpose
