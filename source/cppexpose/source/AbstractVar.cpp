
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
}

PropertyContainer * AbstractVar::parent() const
{
    return m_parent;
}

std::string AbstractVar::typeName() const
{
    // [TODO]
    return "<unknown>";
}

void AbstractVar::registerProperty(const std::string & name, PropertyContainer * parent)
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
