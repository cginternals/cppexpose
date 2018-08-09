
#include <cppexpose/expose/AbstractProperty.h>

#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Array.h>
#include <cppexpose/expose/Variant.h>


namespace cppexpose
{


AbstractProperty::AbstractProperty()
: m_parent(nullptr)
{
}

AbstractProperty::~AbstractProperty()
{
}

PropertyContainer * AbstractProperty::parent() const
{
    return m_parent;
}

void AbstractProperty::registerProperty(const std::string & name, PropertyContainer * parent)
{
    // Check if parent is valid
    if (!parent) return;

    // Check if parent is an Object
    if (Object * obj = parent->asObject()) {
        obj->addProperty(name, this);
    }

    // Check if parent is an Array
    else if (Array * arr = parent->asArray()) {
        arr->push(this);
    }
}


} // namespace cppexpose
