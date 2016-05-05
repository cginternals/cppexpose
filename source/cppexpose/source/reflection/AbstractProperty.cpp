
#include <cppexpose/reflection/AbstractProperty.h>


namespace cppexpose
{


AbstractProperty::AbstractProperty(PropertyGroup * parent)
: m_name("")
, m_parent(parent)
{
}

AbstractProperty::AbstractProperty(const std::string & name, PropertyGroup * parent)
: m_name(name)
, m_parent(parent)
{
}

AbstractProperty::~AbstractProperty()
{
}

std::string AbstractProperty::name() const
{
    return m_name;
}

PropertyGroup * AbstractProperty::parent() const
{
    return m_parent;
}


} // namespace cppexpose
