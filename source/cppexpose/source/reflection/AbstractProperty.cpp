
#include <cppexpose/reflection/AbstractProperty.h>

//#include <cppexpose/reflection/Object.h>


namespace cppexpose
{


AbstractProperty::AbstractProperty(const std::string & name, Object * parent)
: m_parent(nullptr)
, m_name(name)
{
    if (parent)
    {
        // [TODO]
        // parent->addProperty(this);
    }
}

AbstractProperty::~AbstractProperty()
{
    beforeDestroy(this);

    if (m_parent)
    {
        // [TODO]
        // m_parent->removeProperty(this);
    }
}

Object * AbstractProperty::parent() const
{
    return m_parent;
}

const std::string & AbstractProperty::name() const
{
    return m_name;
}

void AbstractProperty::setParent(Object * parent)
{
    m_parent = parent;
}

void AbstractProperty::setName(const std::string & name)
{
    m_name = name;
}


} // namespace cppexpose
