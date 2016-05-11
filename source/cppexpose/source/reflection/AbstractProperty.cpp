
#include <cppexpose/reflection/AbstractProperty.h>

#include <cppexpose/reflection/PropertyGroup.h>


namespace cppexpose
{


AbstractProperty::AbstractProperty()
: m_parent(nullptr)
, m_name("")
{
}

AbstractProperty::~AbstractProperty()
{
}

PropertyGroup * AbstractProperty::parent() const
{
    return m_parent;
}

std::string AbstractProperty::name() const
{
    return m_name;
}

void AbstractProperty::initProperty(PropertyGroup * parent, const std::string & name)
{
    m_parent = parent;
    m_name   = name;

    if (m_parent) {
        m_parent->addProperty(this);
    }
}


} // namespace cppexpose
