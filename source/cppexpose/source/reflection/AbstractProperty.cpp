
#include <cppexpose/reflection/AbstractProperty.h>

#include <cppexpose/reflection/PropertyGroup.h>


namespace cppexpose
{


AbstractProperty::AbstractProperty(PropertyGroup * parent)
: m_name("")
, m_parent(parent)
{
    if (m_parent) {
        m_parent->addProperty(this);
    }
}

AbstractProperty::AbstractProperty(const std::string & name, PropertyGroup * parent)
: m_name(name)
, m_parent(parent)
{
    if (m_parent) {
        m_parent->addProperty(this);
    }
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
