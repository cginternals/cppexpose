
#pragma once


namespace cppexpose
{


template <typename Type, typename BaseType>
Component<Type, BaseType>::Component(
    const std::string & name
  , const std::string & description
  , const std::string & type
  , const std::string & tags
  , const std::string & icon
  , const std::string & annotations
  , const std::string & vendor
  , const std::string & version)
{
    this->m_name        = name;
    this->m_description = description;
    this->m_type        = type;
    this->m_tags        = tags;
    this->m_icon        = icon;
    this->m_annotations = annotations;
    this->m_vendor      = vendor;
    this->m_version     = version;
}

template <typename Type, typename BaseType>
Component<Type, BaseType>::~Component()
{
}


} // namespace cppexpose
