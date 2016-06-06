
#include <cppexpose/reflection/Object.h>

#include <cassert>
#include <typeinfo>

#include <cppexpose/base/string_helpers.h>
#include <cppexpose/variant/Variant.h>


namespace
{
    static const char g_separator = '.';
}


namespace cppexpose
{


Object::Object()
{
    initProperty("", nullptr, PropertyOwnership::None);
}

Object::Object(const std::string & name, Object * parent)
{
    initProperty(name, parent, PropertyOwnership::None);
}

Object::~Object()
{
    clear();
}

void Object::clear()
{
    // Destroy managed properties
    while (m_managedProperties.size() > 0)
    {
        delete m_managedProperties.front();
    }
}

const std::unordered_map<std::string, AbstractProperty *> & Object::properties() const
{
    return m_propertiesMap;
}

bool Object::propertyExists(const std::string & name) const
{
    return m_propertiesMap.find(name) != m_propertiesMap.end();
}

AbstractProperty * Object::property(size_t index)
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

const AbstractProperty * Object::property(size_t index) const
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

AbstractProperty * Object::property(const std::string & path)
{
    std::vector<std::string> splittedPath = helper::split(path, g_separator);
    return const_cast<AbstractProperty *>(findProperty(splittedPath));
}

const AbstractProperty * Object::property(const std::string & path) const
{
    std::vector<std::string> splittedPath = helper::split(path, g_separator);
    return findProperty(splittedPath);
}

bool Object::addProperty(AbstractProperty * property, PropertyOwnership ownership)
{
    // Reject properties that have no name, or whose name already exists,
    // or that already have a parent object.
    if (!property || this->propertyExists(property->name()) || property->parent() != nullptr)
    {
        return false;
    }

    // Set parent
    property->setParent(this);

    // Invoke callback
    auto newIndex = m_properties.size();
    beforeAdd(newIndex, property);

    // Add property
    m_properties.push_back(property);
    m_propertiesMap.insert(std::make_pair(property->name(), property));

    // Take ownership over property?
    if (ownership == PropertyOwnership::Parent)
    {
        m_managedProperties.push_back(property);
    }

    // Invoke callback
    afterAdd(newIndex, property);

    // Success
    return true;
}

bool Object::removeProperty(AbstractProperty * property)
{
    // Reject properties that are not part of the object
    if (!property || property->parent() != this)
    {
        return false;
    }

    // Find property in object
    auto it = std::find(m_properties.begin(), m_properties.end(), property);
    if (it == m_properties.end())
    {
        return false;
    }

    // Get property index
    size_t index = std::distance(m_properties.begin(), it);

    // Invoke callback
    beforeRemove(index, property);

    // Remove property from object
    m_properties.erase(it);
    m_propertiesMap.erase(property->name());

    // Remove from managed list
    auto it2 = std::find(m_managedProperties.begin(), m_managedProperties.end(), property);
    if (it2 != m_managedProperties.end())
    {
        m_managedProperties.erase(it2);
    }

    // Reset property parent
    property->setParent(nullptr);

    // Invoke callback
    afterRemove(index, property);

    // Success
    return true;
}

bool Object::destroyProperty(AbstractProperty * property)
{
    // Check that property exists and belongs to the object
    if (!property || property->parent() != this)
    {
        return false;
    }

    // Chec that property is owned by the object
    auto it = std::find(m_managedProperties.begin(), m_managedProperties.end(), property);
    if (it == m_properties.end())
    {
        return false;
    }

    // Destroy property
    delete property;

    // Property removed
    return true;
}

const std::vector<Method> & Object::functions() const
{
    return m_functions;
}

bool Object::isObject() const
{
    return true;
}

AbstractTyped * Object::clone() const
{
    // [TODO]
    return new Object(name());
}

const std::type_info & Object::type() const
{
    return typeid(Object);
}

std::string Object::typeName() const
{
    return "Object";
}

bool Object::isReadOnly() const
{
    return false;
}

bool Object::isComposite() const
{
    return true;
}

size_t Object::numSubValues() const
{
    return m_properties.size();
}

AbstractTyped * Object::subValue(size_t index)
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

bool Object::isEnum() const
{
    return false;
}

bool Object::isArray() const
{
    return false;
}

bool Object::isVariant() const
{
    return false;
}

bool Object::isString() const
{
    return false;
}

bool Object::isBool() const
{
    return false;
}

bool Object::isNumber() const
{
    return false;
}

bool Object::isIntegral() const
{
    return false;
}

bool Object::isSignedIntegral() const
{
    return false;
}

bool Object::isUnsignedIntegral() const
{
    return false;
}

bool Object::isFloatingPoint() const
{
    return false;
}

Variant Object::toVariant() const
{
    // Create variant map from all properties in the object
    Variant map = Variant::map();
    for (auto it : m_propertiesMap) {
        // Get name and property
        std::string        name = it.first;
        AbstractProperty * prop = it.second;

        // Add to variant map
        (*map.asMap())[name] = prop->toVariant();
    }

    // Return variant representation
    return map;
}

bool Object::fromVariant(const Variant & value)
{
    // Check if variant is a map
    if (!value.isVariantMap()) {
        return false;
    }

    // Get all values from variant map
    for (auto it : *value.asMap()) {
        // Get name and value
        std::string     name = it.first;
        const Variant & var  = it.second;

        // If this names an existing property, set its value
        AbstractProperty * prop = this->property(name);
        if (prop) {
            prop->fromVariant(var);
        }
    }

    // Done
    return true;
}

std::string Object::toString() const
{
    // Convert object into JSON
    SerializerJSON json;
    return json.toString(this->toVariant());
}

bool Object::fromString(const std::string & str)
{
    // Convert from JSON
    Variant values;
    SerializerJSON json;
    if (json.fromString(values, str)) {
        return fromVariant(values);
    }

    // Error
    return false;
}

bool Object::toBool() const
{
    return false;
}

bool Object::fromBool(bool)
{
    return false;
}

long long Object::toLongLong() const
{
    return 0ll;
}

bool Object::fromLongLong(long long)
{
    return false;
}

unsigned long long Object::toULongLong() const
{
    return 0ull;
}

bool Object::fromULongLong(unsigned long long)
{
    return false;
}

double Object::toDouble() const
{
    return 0.0;
}

bool Object::fromDouble(double)
{
    return false;
}

const AbstractProperty * Object::findProperty(const std::vector<std::string> & path) const
{
    // [TODO] Use iterative approach rather than recursion

    // Check if path is valid
    if (path.size() == 0) {
        return nullptr;
    }

    // Check if first element of the path exists in this object
    if (!propertyExists(path.front())) {
        return nullptr;
    }

    // Get the respective property
    AbstractProperty * property = m_propertiesMap.at(path.front());

    // If there are no more sub-paths, return the found property
    if (path.size() == 1) {
        return property;
    }

    // Otherwise, it is an element in the middle of the path, so ensure it is an object
    if (!property->isObject()) {
        return nullptr;
    }

    // Call recursively on sub-object
    return static_cast<Object *>(property)->findProperty({ path.begin() + 1, path.end() });
}


} // namespace cppexpose
