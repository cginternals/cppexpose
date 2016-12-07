
#include <cppexpose/reflection/AbstractProperty.h>

#include <cppexpose/reflection/Object.h>


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

void AbstractProperty::setName(const std::string & name)
{
    m_name = name;
}

Object * AbstractProperty::parent() const
{
    return m_parent;
}

bool AbstractProperty::hasParent() const
{
    return m_parent != nullptr;
}

const VariantMap & AbstractProperty::options() const
{
    return m_options;
}

void AbstractProperty::setOptions(const VariantMap & map)
{
    // Copy options
    for (const auto & pair : map)
    {
        m_options[pair.first] = pair.second;
        optionChanged(pair.first);
    }
}

bool AbstractProperty::hasOption(const std::string & key) const
{
    return m_options.count(key) != 0;
}

Variant AbstractProperty::option(const std::string & key) const
{
    if (!this->hasOption(key))
    {
        return Variant();
    }

    return m_options.at(key);
}

void AbstractProperty::setOption(const std::string & key, const Variant & value)
{
    m_options[key] = value;
    optionChanged(key);
}

bool AbstractProperty::removeOption(const std::string & key)
{
    if (!this->hasOption(key))
    {
        return false;
    }

    m_options.erase(key);
    optionChanged(key);

    return true;
}

void AbstractProperty::initProperty(const std::string & name, Object * parent, PropertyOwnership ownership)
{
    // Store name
    m_name = name;

    // Is not desired as parent->addProperty updates the m_parent but asserts beforehand that this property has no parent set.
    // m_parent = parent;

    // Add property to parent object
    if (parent)
    {
        parent->addProperty(this, ownership);
    }
}

void AbstractProperty::setParent(Object * parent)
{
    m_parent = parent;
}


} // namespace cppexpose
