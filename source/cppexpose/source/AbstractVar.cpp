
#include <cppexpose/AbstractVar.h>

#include <vector>

#include <cppassist/string/manipulation.h>

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

const AbstractVar * AbstractVar::resolve(const std::string & path) const
{
    // Split path into subpaths
    std::vector<std::string> subpaths = cppassist::string::split(path, '.', true);

    // Start with this property
    const AbstractVar * property = this;

    // Find property relative to this property
    auto current = subpaths.begin();
    const auto end = subpaths.end();
    while (current != end)
    {
        // Get property name (first part of the path)
        const std::string & name = *current;

        // Resolve relative path
        if (name == "parent")
        {
            // Parent property
            property = property->parent();
        }
        else if (property->isObject() || property->isObjectPointer())
        {
            // Get object
            const Object * object = property->asObject();
            if (object) {
                // Get relative property
                property = object->property(name);
            } else {
                // Cannot traverse further
                property = nullptr;
            }
        }

        // Check if property exists
        if (!property) {
            return nullptr;
        }

        // Compute next path segment
        ++current;

        // If there are no more sub-paths, return the found property
        if (current == end) {
            return property;
        }
    }

    return nullptr;
}


} // namespace cppexpose
