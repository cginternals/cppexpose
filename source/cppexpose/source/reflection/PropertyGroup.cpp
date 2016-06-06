
#include <cppexpose/reflection/PropertyGroup.h>
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


PropertyGroup::PropertyGroup()
{
    initProperty("", nullptr, PropertyOwnership::None);
}

PropertyGroup::PropertyGroup(const std::string & name, PropertyGroup * parent)
{
    initProperty(name, parent, PropertyOwnership::None);
}

PropertyGroup::~PropertyGroup()
{
    clear();
}

void PropertyGroup::clear()
{
    // Destroy managed properties
    while (m_managedProperties.size() > 0)
    {
        delete m_managedProperties.front();
    }
}

const std::unordered_map<std::string, AbstractProperty *> & PropertyGroup::properties() const
{
    return m_propertiesMap;
}

bool PropertyGroup::propertyExists(const std::string & name) const
{
    return m_propertiesMap.find(name) != m_propertiesMap.end();
}

AbstractProperty * PropertyGroup::property(size_t index)
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

const AbstractProperty * PropertyGroup::property(size_t index) const
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

AbstractProperty * PropertyGroup::property(const std::string & path)
{
    std::vector<std::string> splittedPath = helper::split(path, g_separator);
    return const_cast<AbstractProperty *>(findProperty(splittedPath));
}

const AbstractProperty * PropertyGroup::property(const std::string & path) const
{
    std::vector<std::string> splittedPath = helper::split(path, g_separator);
    return findProperty(splittedPath);
}

bool PropertyGroup::addProperty(AbstractProperty * property, PropertyOwnership ownership)
{
    // Reject properties that have no name, or whose name already exists,
    // or that already have a parent group
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

bool PropertyGroup::removeProperty(AbstractProperty * property)
{
    // Reject properties that are not part of the group
    if (!property || property->parent() != this)
    {
        return false;
    }

    // Find property in group
    auto it = std::find(m_properties.begin(), m_properties.end(), property);
    if (it == m_properties.end())
    {
        return false;
    }

    // Get property index
    size_t index = std::distance(m_properties.begin(), it);

    // Invoke callback
    beforeRemove(index, property);

    // Remove property from group
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

bool PropertyGroup::destroyProperty(AbstractProperty * property)
{
    // Check that property exists and belongs to the group
    if (!property || property->parent() != this)
    {
        return false;
    }

    // Chec that property is owned by the group
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

bool PropertyGroup::groupExists(const std::string & name) const
{
    return (this->propertyExists(name) && m_propertiesMap.at(name)->isGroup());
}

PropertyGroup * PropertyGroup::group(const std::string & path)
{
    // Get property by path
    AbstractProperty * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into group
    return static_cast<PropertyGroup *>(property);
}

const PropertyGroup * PropertyGroup::group(const std::string & path) const
{
    // Get property by path
    const AbstractProperty * property = this->property(path);
    if (!property) {
        return nullptr;
    }

    // Convert into group
    return static_cast<const PropertyGroup *>(property);
}

const std::vector<Method> & PropertyGroup::functions() const
{
    return m_functions;
}

bool PropertyGroup::isGroup() const
{
    return true;
}

AbstractTyped * PropertyGroup::clone() const
{
    // [TODO]
    return new PropertyGroup(name());
}

const std::type_info & PropertyGroup::type() const
{
    return typeid(PropertyGroup);
}

std::string PropertyGroup::typeName() const
{
    return "PropertyGroup";
}

bool PropertyGroup::isReadOnly() const
{
    return false;
}

bool PropertyGroup::isComposite() const
{
    return true;
}

size_t PropertyGroup::numSubValues() const
{
    return m_properties.size();
}

AbstractTyped * PropertyGroup::subValue(size_t index)
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

bool PropertyGroup::isEnum() const
{
    return false;
}

bool PropertyGroup::isArray() const
{
    return false;
}

bool PropertyGroup::isVariant() const
{
    return false;
}

bool PropertyGroup::isString() const
{
    return false;
}

bool PropertyGroup::isBool() const
{
    return false;
}

bool PropertyGroup::isNumber() const
{
    return false;
}

bool PropertyGroup::isIntegral() const
{
    return false;
}

bool PropertyGroup::isSignedIntegral() const
{
    return false;
}

bool PropertyGroup::isUnsignedIntegral() const
{
    return false;
}

bool PropertyGroup::isFloatingPoint() const
{
    return false;
}

Variant PropertyGroup::toVariant() const
{
    // Create variant map from all properties in the group
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

bool PropertyGroup::fromVariant(const Variant & value)
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

std::string PropertyGroup::toString() const
{
    // Convert group into JSON
    SerializerJSON json;
    return json.toString(this->toVariant());
}

bool PropertyGroup::fromString(const std::string & str)
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

bool PropertyGroup::toBool() const
{
    return false;
}

bool PropertyGroup::fromBool(bool)
{
    return false;
}

long long PropertyGroup::toLongLong() const
{
    return 0ll;
}

bool PropertyGroup::fromLongLong(long long)
{
    return false;
}

unsigned long long PropertyGroup::toULongLong() const
{
    return 0ull;
}

bool PropertyGroup::fromULongLong(unsigned long long)
{
    return false;
}

double PropertyGroup::toDouble() const
{
    return 0.0;
}

bool PropertyGroup::fromDouble(double)
{
    return false;
}

const AbstractProperty * PropertyGroup::findProperty(const std::vector<std::string> & path) const
{
    // [TODO] Use iterative approach rather than recursion

    // Check if path is valid
    if (path.size() == 0) {
        return nullptr;
    }

    // Check if first element of the path exists in this group
    if (!propertyExists(path.front())) {
        return nullptr;
    }

    // Get the respective property
    AbstractProperty * property = m_propertiesMap.at(path.front());

    // If there are no more sub-paths, return the found property
    if (path.size() == 1) {
        return property;
    }

    // Otherwise, it is an element in the middle of the path, so ensure it is a group
    if (!property->isGroup()) {
        return nullptr;
    }

    // Call recursively on subgroup
    return static_cast<PropertyGroup *>(property)->findProperty({ path.begin() + 1, path.end() });
}


} // namespace cppexpose
