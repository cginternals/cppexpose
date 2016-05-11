
#include <cppexpose/reflection/PropertyGroup.h>

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


PropertyGroup::PropertyGroup(PropertyGroup * parent)
{
    initProperty(parent, "");
}

PropertyGroup::PropertyGroup(const std::string & name, PropertyGroup * parent)
{
    initProperty(parent, name);
}

PropertyGroup::~PropertyGroup()
{
    clear();
}

void PropertyGroup::clear()
{
    // Destroy managed properties
    for (AbstractProperty * property : m_managedProperties)
    {
        delete property;
    }
    m_managedProperties.clear();

    // Remove all properties
    auto it = m_properties.begin();
    while (it != m_properties.end())
    {
        // Get property index
        size_t index = std::distance(m_properties.begin(), it);

        // Invoke callback
        beforeRemove(index);

        // Remove property
        m_propertiesMap.erase((*it)->name());
        it = m_properties.erase(it);

        // Invoke callback
        afterRemove(index);
    }

    // Make sure that property list is empty
    assert(m_properties.empty());
    assert(m_propertiesMap.empty());
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

AbstractProperty * PropertyGroup::addProperty(AbstractProperty * property)
{
    // Reject properties that have no name or whose name already exists
    if (!property || this->propertyExists(property->name()))
    {
        return nullptr;
    }

    // Invoke callback
    beforeAdd(m_properties.size(), property);

    // Add property
    m_properties.push_back(property);
    m_propertiesMap.insert(std::make_pair(property->name(), property));

    // Invoke callback
    afterAdd(m_properties.size(), property);

    // Return pointer to property
    return property;
}

void PropertyGroup::takeOwnership(AbstractProperty * property)
{
    // Check property
    if (!property ||
        std::find(m_managedProperties.begin(), m_managedProperties.end(), property) != m_managedProperties.end())
    {
        return;
    }

    // Put property into managed list
    m_managedProperties.push_back(property);
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
