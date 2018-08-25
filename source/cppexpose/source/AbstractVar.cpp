
#include <cppexpose/AbstractVar.h>

#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


AbstractVar::AbstractVar()
: m_parent(nullptr)
{
}

AbstractVar::~AbstractVar()
{
    beforeDestroy();
}

PropertyContainer * AbstractVar::parent() const
{
    return m_parent;
}

void AbstractVar::setParent(PropertyContainer * parent)
{
    if (!m_parent || !parent) {
        m_parent = parent;
    }
}

std::string AbstractVar::typeName() const
{
    // [TODO]
    return "<unknown>";
}

void AbstractVar::registerProperty(PropertyContainer * parent, const std::string & name)
{
    // Check if parent is valid
    if (!parent) return;

    // Check if parent is an Object
    if (Object * obj = const_cast<Object *>(parent->asObject())) {
        obj->addProperty(name, this);
    }

    // Check if parent is an Array
    else if (Array * arr = const_cast<Array *>(parent->asArray())) {
        arr->push(this);
    }
}


} // namespace cppexpose
