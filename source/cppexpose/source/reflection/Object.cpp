
#include <cppexpose/type/type_system.h>

#include <cassert>
#include <typeinfo>

#include <unordered_set>

#include <cppassist/string/manipulation.h>

#include <cppexpose/type/ObjectType.h>
#include <cppexpose/json/JSON.h>


namespace
{
    const char g_separator = '.';
    const std::string g_separatorString = ".";
    const std::string g_parent = "parent";
}


namespace cppexpose
{


Object::Object(const std::string & name, Object * parent)
: AbstractProperty(name != "" ? name : "Object", parent)
{
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
    // Reject properties that have no name, whose name already exists,
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
    // Add property to object
    const auto success = addProperty(property.get());

    // If property has been added to the object, take ownership over it
    if (success)
    {
        m_managedProperties.push_back(std::move(property));
    }

    // Return status
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
    auto it2 = std::find_if(m_managedProperties.begin(), m_managedProperties.end(),
        [property] (const std::unique_ptr<AbstractProperty> & managedProperty)
        {
            return managedProperty.get() == property;
        } );
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

Variant Object::toVariant() const
{
    // Create variant map from all properties in the object
    Variant map = Variant::map();

    for (const auto & it : m_propertiesMap)
    {
        // Get name and property
        const std::string & name = it.first;
        AbstractProperty *  prop = it.second;

        // Add to variant map
        map.setElement(name, prop->toVariant());
    }

    // Return variant representation
    return map;
}

bool Object::fromVariant(const Variant & value)
{
    // Check if variant is a map
    if (!value.isMap())
    {
        return false;
    }

    // Get all values from variant map
    for (const auto & name : value.keys())
    {
        // Get name and value
        const Variant & var = value.element(name);

        // If this names an existing property, set its value
        AbstractProperty * prop = this->property(name);
        if (prop)
        {
            prop->fromVariant(var);
        }
    }

    // Done
    return true;
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

Type & Object::type()
{
    static Type type(std::make_shared<ObjectType>());

    return type;
}

const Type & Object::type() const
{
    static Type type(std::make_shared<ObjectType>());

    return type;
}

const AbstractBaseType * Object::baseType() const
{
    return nullptr;
}

AbstractBaseType * Object::baseType()
{
    return nullptr;
}

Type & Object::elementType()
{
    static Type type(std::make_shared<ObjectType>());

    return type;
}

const Type & Object::elementType() const
{
    static Type type(std::make_shared<ObjectType>());

    return type;
}

const std::string & Object::typeName() const
{
    return type().typeName();
}

bool Object::isNull() const
{
    return type().isNull();
}

bool Object::isConst() const
{
    return type().isConst();
}

bool Object::isArray() const
{
    return type().isArray();
}

bool Object::isDynamicArray() const
{
    return type().isDynamicArray();
}

bool Object::isMap() const
{
    return type().isMap();
}

bool Object::isBoolean() const
{
    return type().isBoolean();
}

bool Object::isNumber() const
{
    return type().isNumber();
}

bool Object::isIntegral() const
{
    return type().isIntegral();
}

bool Object::isUnsigned() const
{
    return type().isUnsigned();
}

bool Object::isFloatingPoint() const
{
    return type().isFloatingPoint();
}

bool Object::isString() const
{
    return type().isString();
}

bool Object::isType() const
{
    return type().isType();
}

std::unique_ptr<AbstractValueContainer> Object::createCopy() const
{
    // TODO: not implemented
    return nullptr;
}

bool Object::compareTypeAndValue(const AbstractValueContainer & value) const
{
    // TOOD: maybe wrong implementation
    return this == &value;
}

std::string Object::toString() const
{
    // TODO: not implemented (convert to JSON?)
    return "";
}

bool Object::fromString(const std::string & value)
{
    // TODO: not implemented (convert from JSON?)
    return false;
}

bool Object::toBool() const
{
    return false;
}

bool Object::fromBool(bool value)
{
    return false;
}

long long Object::toLongLong() const
{
    return 0;
}

bool Object::fromLongLong(long long value)
{
    return false;
}

unsigned long long Object::toULongLong() const
{
    return 0;
}

bool Object::fromULongLong(unsigned long long value)
{
    return false;
}

double Object::toDouble() const
{
    return 0.0;
}

bool Object::fromDouble(double value)
{
    return false;
}

size_t Object::numElements() const
{
    return 0;
}

Variant Object::element(size_t i) const
{
    return Variant();
}

void Object::setElement(size_t i, const Variant & value)
{
}

void Object::pushElement(const Variant & value)
{
}

std::vector<std::string> Object::keys() const
{
    return std::vector<std::string>();
}

Variant Object::element(const std::string & key) const
{
    return Variant();
}

void Object::setElement(const std::string & key, const Variant & value)
{
}


} // namespace cppexpose
