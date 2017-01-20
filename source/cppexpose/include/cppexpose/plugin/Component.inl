
#pragma once


namespace cppexpose
{


template <typename Type, typename BaseType, typename Enable>
Component<Type, BaseType, Enable>::Component(
    const std::string & name
  , const std::string & description
  , const std::string & type
  , const std::string & tags
  , const std::string & icon
  , const std::string & annotations
  , const std::string & vendor
  , const std::string & version)
: TypedComponent<BaseType>(name, description, type, tags, icon, annotations, vendor, version)
{
}

template <typename Type, typename BaseType, typename Enable>
Component<Type, BaseType, Enable>::~Component()
{
}

template <typename Type, typename BaseType, typename Enable>
BaseType * Component<Type, BaseType, Enable>::createInstance() const
{
    return new Type();
}


} // namespace cppexpose
