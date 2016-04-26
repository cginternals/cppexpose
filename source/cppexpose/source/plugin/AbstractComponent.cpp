
#include <cppexpose/plugin/AbstractComponent.h>


namespace cppexpose
{


AbstractComponent::AbstractComponent(
    const std::string & name
  , const std::string & description
  , const std::string & type
  , const std::string & subtype
  , const std::string & annotations
  , const std::string & vendor
  , const std::string & version)
: m_name(name)
, m_description(description)
, m_type(type)
, m_subtype(subtype)
, m_annotations(annotations)
, m_vendor(vendor)
, m_version(version)
{
}

AbstractComponent::~AbstractComponent()
{
}

const char * AbstractComponent::name() const
{
    return m_name.c_str();
}

const char * AbstractComponent::description() const
{
    return m_description.c_str();
}

const char * AbstractComponent::type() const
{
    return m_type.c_str();
}

const char * AbstractComponent::subtype() const
{
    return m_subtype.c_str();
}

const char * AbstractComponent::annotations() const
{
    return m_annotations.c_str();
}

const char * AbstractComponent::vendor() const
{
    return m_vendor.c_str();
}

const char * AbstractComponent::version() const
{
    return m_version.c_str();
}

const cpplocate::ModuleInfo & AbstractComponent::moduleInfo() const
{
    return m_moduleInfo;
}

void AbstractComponent::setModuleInfo(const cpplocate::ModuleInfo & moduleInfo)
{
    m_moduleInfo = moduleInfo;
}


} // namespace cppexpose
