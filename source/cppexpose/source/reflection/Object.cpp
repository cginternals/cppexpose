
#include <cppexpose/reflection/Object.h>

#include <cassert>
#include <typeinfo>

#include <unordered_set>

#include <cppassist/string/manipulation.h>

#include <cppexpose/json/JSON.h>


namespace
{
    const char g_separator = '.';
    const std::string g_separatorString = ".";
    const std::string g_parent = "parent";
}


namespace cppexpose
{


Object::Object()
: Object("")
{
}

Object::Object(const std::string & name)
: m_className("Object")
{
    initProperty(name, nullptr);
}

Object::~Object()
{
    clear();
}

const std::string & Object::className() const
{
    return m_className;
}

void Object::setClassName(const std::string & className)
{
    m_className = className;
}

void Object::clear()
{
    // Remove properties
    // removeProperty() modifies m_properties, so don't use iterators here!
    while (!m_properties.empty())
    {
        removeProperty(m_properties.back());
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
    std::vector<std::string> splittedPath = cppassist::string::split(path, g_separator);
    return const_cast<AbstractProperty *>(findProperty(splittedPath));
}

const AbstractProperty * Object::property(const std::string & path) const
{
    std::vector<std::string> splittedPath = cppassist::string::split(path, g_separator);
    return findProperty(splittedPath);
}

bool Object::addProperty(AbstractProperty * property)
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

    // Invoke callback
    afterAdd(newIndex, property);

    // Success
    return true;
}


bool Object::addProperty(std::unique_ptr<AbstractProperty> && property)
{
    const auto success = addProperty(property.get());
    if (success)
    {
        m_managedProperties.push_back(std::move(property));
    }

    return success;
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

    // Reset property parent
    property->setParent(nullptr);

    // Invoke callback
    afterRemove(index, property);

    // Remove from managed list (deletes the property)
    auto it2 = std::find_if(m_managedProperties.begin(), m_managedProperties.end(), [property](const std::unique_ptr<AbstractProperty> & managedProperty) { return managedProperty.get() == property; });
    if (it2 != m_managedProperties.end())
    {
        m_managedProperties.erase(it2);
    }

    // Success
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

std::unique_ptr<AbstractTyped> Object::clone() const
{
    // [TODO]
    return cppassist::make_unique<Object>(name());
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
    for (const auto & it : m_propertiesMap) {
        // Get name and property
        const std::string & name = it.first;
        AbstractProperty *  prop = it.second;

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
    for (const auto & it : *value.asMap()) {
        // Get name and value
        const std::string & name = it.first;
        const Variant &     var  = it.second;

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
    return JSON::stringify(this->toVariant());
}

bool Object::fromString(const std::string & str)
{
    // Convert from JSON
    Variant values;
    if (JSON::parse(values, str)) {
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

std::string Object::relativePathTo(const Object * const other) const
{
    // Return "." if the objects are the same
    if (this == other) {
        return g_separatorString;
    }

    // Find all ancestors of "this"
    std::unordered_set<const Object*> ancestors;

    const Object * curObject = this;
    while (curObject)
    {
        ancestors.insert(curObject);
        curObject = curObject->parent();
    }

    // Find the common parent from "other"
    std::vector<std::string> otherPath;
    const Object * commonParent = nullptr;

    curObject = other;
    while (curObject)
    {
        if (ancestors.count(curObject))
        {
            commonParent = curObject;
            break;
        }

        otherPath.push_back(curObject->name());
        curObject = curObject->parent();
    }

    // Abort if no common parent has been found
    if (!commonParent) {
        return "";
    }

    // Count number of steps from this to the common parent
    curObject = this;
    size_t numParents = 0;
    while (curObject != commonParent)
    {
        numParents++;
        curObject = curObject->parent();
    }

    // Compose string
    std::string relativePath = "";

    for (size_t i = 0; i < numParents; i++)
    {
        relativePath += (i == 0) ? "parent" : ".parent";
    }

    for (size_t i = 0; i < otherPath.size(); i++)
    {
        relativePath += "." + otherPath[otherPath.size() - 1 - i];
    }

    return relativePath;
}

const AbstractProperty * Object::findProperty(const std::vector<std::string> & path) const
{
    // Find property
    const AbstractProperty * property = this;

    auto current = path.begin();
    const auto end = path.end();

    while (current != end)
    {
        // Get property name (first part of the path)
        const std::string & name = *current;

        if (name == g_parent)
        {
            // Parent property
            property = property->m_parent;
        }
        else
        {
            // Sub-property
            auto object = static_cast<const Object *>(property);
            const auto it = object->m_propertiesMap.find(name);

            if (it != object->m_propertiesMap.end())
            {
                property = it->second;
            }
            else
            {
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

        // Otherwise, it is an element in the middle of the path, so ensure it is an object
        if (!property->isObject()) {
            return nullptr;
        }
    }

    return nullptr;
}


} // namespace cppexpose
