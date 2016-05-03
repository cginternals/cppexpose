
#pragma once


#include <cppexpose/plugin/Component.h>


namespace cppexpose
{


template <typename Type, typename BaseType>
Component<Type, BaseType>::Component(
    const std::string & name
  , const std::string & description
  , const std::string & type
  , const std::string & subtype
  , const std::string & icon
  , const std::string & annotations
  , const std::string & vendor
  , const std::string & version)
: TypedComponent<BaseType>(name, description, type, subtype, icon, annotations, vendor, version)
{
}

template <typename Type, typename BaseType>
Component<Type, BaseType>::~Component()
{
}

template <typename Type, typename BaseType>
BaseType * Component<Type, BaseType>::createInstance() const
{
    return new Type(this->m_moduleInfo);
}


} // namespace cppexpose
