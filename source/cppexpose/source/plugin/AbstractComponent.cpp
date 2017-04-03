
#include <cppexpose/plugin/AbstractComponent.h>


namespace cppexpose
{


AbstractComponent::AbstractComponent()
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

const char * AbstractComponent::tags() const
{
    return m_tags.c_str();
}

const char * AbstractComponent::icon() const
{
    return m_icon.c_str();
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


} // namespace cppexpose
