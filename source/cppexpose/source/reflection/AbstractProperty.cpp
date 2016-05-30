
#include <cppexpose/reflection/AbstractProperty.h>

#include <cppexpose/reflection/PropertyGroup.h>


namespace cppexpose
{


AbstractProperty::AbstractProperty()
: m_name("")
, m_parent(nullptr)
{
}

AbstractProperty::~AbstractProperty()
{
    if (m_parent) {
        m_parent->unregisterProperty(this);
    }
}

std::string AbstractProperty::name() const
{
    return m_name;
}

PropertyGroup * AbstractProperty::parent() const
{
    return m_parent;
}

void AbstractProperty::initProperty(const std::string & name, PropertyGroup * parent)
{
    m_name   = name;
    m_parent = parent;

    if (m_parent) {
        m_parent->registerProperty(this);
    }
}


} // namespace cppexpose
