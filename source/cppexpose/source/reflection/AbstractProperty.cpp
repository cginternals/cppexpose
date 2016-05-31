
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
    beforeDestroy(this);

    if (m_parent)
    {
        m_parent->removeProperty(this);
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

void AbstractProperty::initProperty(const std::string & name, PropertyGroup * parent, PropertyOwnership ownership)
{
    // Store name
    m_name = name;

    // Is not desired as parent->addProperty updates the m_parent but asserts beforehand that this property has no parent set.
    // m_parent = parent;

    // Add property to the parent group
    if (parent)
    {
        parent->addProperty(this, ownership);
    }
}

void AbstractProperty::setParent(PropertyGroup * parent)
{
    m_parent = parent;
}


} // namespace cppexpose
