
#include <cppexpose/expose/AbstractVar.h>

#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Array.h>


namespace cppexpose
{


AbstractVar::AbstractVar()
: m_parent(nullptr)
{
}

AbstractVar::~AbstractVar()
{
}

PropertyContainer * AbstractVar::parent() const
{
    return m_parent;
}

void AbstractVar::registerProperty(const std::string & name, PropertyContainer * parent)
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
