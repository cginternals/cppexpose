
#include <cppexpose/expose/Object.h>

#include <algorithm>
#include <iostream>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/expose/Array.h>
#include <cppexpose/expose/Variant.h>
#include <cppexpose/expose/AbstractVar.h>


namespace cppexpose
{


Object Object::create()
{
    std::cout << "Object::create()" << std::endl;

    return std::move(Object());
}

Object::Object()
{
    std::cout << "Object()" << std::endl;
}

Object::Object(const std::string & name, PropertyContainer * parent)
{
    std::cout << "Object(name, parent)" << std::endl;
    registerProperty(name, parent);
}

Object::Object(const Object & obj)
: PropertyContainer()
{
    std::cout << "Object(obj &)" << std::endl;

    copyFromObject(obj);
}

Object::Object(Object && obj)
: PropertyContainer()
{
    // [willy]

    std::cout << "Object(obj &&)" << std::endl;

    // [TODO] We ignore non-owned properties for now, they will have to be copied instead of moved

    // Move owned properties
    for (auto & ptr : obj.m_ownProperties) {
        m_ownProperties.push_back(std::move(ptr));
    }
    obj.m_ownProperties.clear();
}

Object::~Object()
{
    std::cout << "~Object()" << std::endl;
}

bool Object::empty() const
{
    return m_properties.empty();
}

const std::vector<std::string> & Object::properties() const
{
    // Check if property names have already been determined
    if (m_propertyNames.size() > 0) {
        return m_propertyNames;
    }

    // Gather list of property names
    for (auto it : m_properties) {
        m_propertyNames.push_back(it.first);
    }

    // Return list
    return m_propertyNames;
}

bool Object::propertyExists(const std::string & name) const
{
    return m_properties.find(name) != m_properties.end();
}

const AbstractVar * Object::property(const std::string & name) const
{
    const AbstractVar * property = nullptr;

    // Find property
    const auto it = m_properties.find(name);
    if (it != m_properties.end())
    {
        property = it->second;
    }

    // Return property if found
    return property;
}

AbstractVar * Object::property(const std::string & name)
{
    AbstractVar * property = nullptr;

    // Find property
    const auto it = m_properties.find(name);
    if (it != m_properties.end())
    {
        property = it->second;
    }

    // Return property if found
    return property;
}

AbstractVar * Object::addProperty(const std::string & name, AbstractVar * property)
{
    // Reject properties that have no name, or whose name already exists,
    // or that already have a parent object.
    if (!property || this->propertyExists(name) || property->parent() != nullptr)
    {
        return nullptr;
    }

    // Set parent
    // [TODO]
//  property->setParent(this);

    // Invoke callback
    // [TODO]
//  auto newIndex = m_properties.size();
//  beforeAdd(newIndex, property);

    // Add property
    // [TODO]
//  m_properties.push_back(property);
    m_properties.insert(std::make_pair(name, property));

    // Invoke callback
    // [TODO]
//  afterAdd(newIndex, property);

    // Reset list of property names
    m_propertyNames.clear();

    // Success
    return property;
}

AbstractVar * Object::addProperty(const std::string & name, AbstractVar && property)
{
    // [willy]

    // Move property to a new instance
    auto movedProperty = property.move();

    // Add property
    const auto propertyPtr = addProperty(name, movedProperty.get());
    if (propertyPtr)
    {
        // Manage property
        m_ownProperties.push_back(std::move(movedProperty));

        // Return property
        return propertyPtr;
    }

    // Failed
    return nullptr;
}

AbstractVar * Object::addProperty(const std::string & name, std::unique_ptr<AbstractVar> && property)
{
    // Add property
    const auto propertyPtr = addProperty(name, property.get());
    if (propertyPtr)
    {
        // Manage property
        m_ownProperties.push_back(std::move(property));

        // Return property
        return propertyPtr;
    }

    // Failed
    return nullptr;
}

bool Object::removeProperty(AbstractVar * property)
{
    // Reject properties that are not part of the object
    if (!property || property->parent() != this)
    {
        return false;
    }

    // Find property in object
    auto it = std::find_if(m_properties.begin(), m_properties.end(), [property] (const std::pair<std::string, AbstractVar *> & pair)
    {
        return pair.second == property;
    });

    // Abort if property is not part of the object
    if (it == m_properties.end())
    {
        return false;
    }

    // Invoke callback
    // [TODO]
//  size_t index = std::distance(m_properties.begin(), it);
//  beforeRemove(index, property);

    // Remove property from object
    m_properties.erase(it);

    // Reset property parent
    // [TODO]
//  property->setParent(nullptr);

    // Invoke callback
    // [TODO]
//  afterRemove(index, property);

    // Check if property is owned by the object
    auto it2 = std::find_if(m_ownProperties.begin(), m_ownProperties.end(), [property] (const std::unique_ptr<AbstractVar> & managedProperty)
    {
        return managedProperty.get() == property;
    });

    // If yes, remove from managed list (delete property)
    if (it2 != m_ownProperties.end())
    {
        m_ownProperties.erase(it2);
    }

    // Reset list of property names
    m_propertyNames.clear();

    // Success
    return true;
}

AbstractVar * Object::clone() const
{
    return new Object(*this);
}

std::unique_ptr<AbstractVar> Object::move()
{
    // [willy]
    return cppassist::make_unique<Object>(std::move(*this));
}

VarType Object::type() const
{
    return VarType::Object;
}

bool Object::isNull() const
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

bool Object::isFloatingPoint() const
{
    return false;
}

bool Object::isEnum() const
{
    return false;
}

bool Object::isString() const
{
    return false;
}

bool Object::isExternal() const
{
    return false;
}

bool Object::isPointer() const
{
    return false;
}

bool Object::isObject() const
{
    return true;
}

bool Object::isArray() const
{
    return false;
}

bool Object::isFunction() const
{
    return false;
}

bool Object::isConst() const
{
    return false;
}

Variant Object::minimumValue() const
{
    return Variant();
}

Variant Object::maximumValue() const
{
    return Variant();
}

bool Object::canConvertToString() const
{
    return true;
}

std::string Object::toString() const
{
    // [TODO]
    return "";
}

bool Object::canConvertToBool() const
{
    return false;
}

bool Object::toBool() const
{
    return false;
}

bool Object::canConvertToLongLong() const
{
    return false;
}

long long Object::toLongLong() const
{
    return 0l;
}

bool Object::canConvertToULongLong() const
{
    return false;
}

unsigned long long Object::toULongLong() const
{
    return 0ul;
}

bool Object::canConvertToDouble() const
{
    return false;
}

double Object::toDouble() const
{
    return 0.0;
}

bool Object::canConvertToObject() const
{
    return true;
}

Object Object::toObject() const
{
    return *this;
}

bool Object::canConvertToArray() const
{
    return false;
}

Array Object::toArray() const
{
    return Array();
}

bool Object::canConvertFromVar(const AbstractVar & value)
{
    return (value.isObject() || value.canConvertToObject());
}

void Object::fromVar(const AbstractVar & value)
{
    if (value.isObject()) {
        const Object & obj = static_cast<const Object &>(value);
        copyFromObject(obj);
    } else if (value.canConvertToObject()) {
        Object obj = value.toObject();
        copyFromObject(obj);
    }
}

const Object * Object::asObject() const
{
    return this;
}

Object * Object::asObject()
{
    return this;
}

void Object::copyFromObject(const Object &)
{
    // [TODO]
}


} // namespace cppexpose
