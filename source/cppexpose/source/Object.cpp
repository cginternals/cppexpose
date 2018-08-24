
#include <cppexpose/Object.h>

#include <algorithm>
#include <sstream>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/Array.h>
#include <cppexpose/Variant.h>
#include <cppexpose/AbstractVar.h>


namespace cppexpose
{


Object Object::create()
{
    return std::move(Object());
}

Object::Object()
{
}

Object::Object(PropertyContainer * parent, const std::string & name)
{
    registerProperty(parent, name);
}

Object::Object(const Object & obj)
: PropertyContainer()
{
    copyFromObject(obj);
}

Object::Object(Object && obj)
: PropertyContainer()
{
    // Move properties
    for (auto it : obj.m_properties) {
        // Get name and property
        std::string name = it.first;
        AbstractVar * var = it.second;

        // Check if property is owned by the object
        auto it2 = obj.m_ownProperties.find(name);
        if (it2 != obj.m_ownProperties.end()) {
            // Move unique_ptr directly
            addProperty(name, std::move(it2->second));
        } else {
            // Move property by function call
            addProperty(name, var->move());
        }
    }

    // Clear properties on source object
    obj.m_properties.clear();
    obj.m_ownProperties.clear();
}

Object::~Object()
{
}

Object & Object::operator =(const AbstractVar & var)
{
    fromVar(var);
    return *this;
}

bool Object::empty() const
{
    return m_properties.empty();
}

const std::unordered_map<std::string, AbstractVar *> & Object::properties() const
{
    return m_properties;
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
    beforeAdd(name, property);

    // Add property
    m_properties.insert(std::make_pair(name, property));

    // Invoke callback
    afterAdd(name, property);

    // Success
    return property;
}

AbstractVar * Object::addProperty(const std::string & name, AbstractVar && property)
{
    // Move property to a new instance
    auto movedProperty = property.move();

    // Add property
    const auto propertyPtr = addProperty(name, movedProperty.get());
    if (propertyPtr)
    {
        // Manage property
        m_ownProperties[name] = std::move(movedProperty);

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
        m_ownProperties[name] = std::move(property);

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

    // Get property name
    std::string name = it->first;

    // Invoke callback
    beforeRemove(name, property);

    // Remove property from object
    m_properties.erase(it);

    // Reset property parent
    // [TODO]
//  property->setParent(nullptr);

    // Invoke callback
    afterRemove(name, property);

    // Check if property is owned by the object
    // If yes, remove from managed list (delete property)
    auto it2 = m_ownProperties.find(name);
    if (it2 != m_ownProperties.end())
    {
        m_ownProperties.erase(it2);
    }

    // Success
    return true;
}

std::unique_ptr<AbstractVar> Object::clone() const
{
    return std::unique_ptr<AbstractVar>(new Object(*this));
}

std::unique_ptr<AbstractVar> Object::move()
{
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

bool Object::isObjectPointer() const
{
    return false;
}

bool Object::isArray() const
{
    return false;
}

bool Object::isArrayPointer() const
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
    std::stringstream ss;

    // Begin object
    ss << "{";

    // Iterate over properties
    bool first = true;
    for (auto it : m_properties) {
        // Get name and property
        std::string   name = it.first;
        AbstractVar * var  = it.second;

        // Ignore certain types of var
        if (var->isNull() || var->isFunction()) {
            continue;
        }

        // Output comma between two properties
        if (!first) {
            ss << ", ";
        } else first = false;

        // Output property name
        ss << "\"" << name << "\"" << ": ";

        // Output property value
        if (var->isString()) ss << "\"";
        ss << var->toString();
        if (var->isString()) ss << "\"";
    }

    // End object
    ss << "}";

    // Return string
    return ss.str();
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

const Array * Object::asArray() const
{
    return nullptr;
}

void Object::copyFromObject(const Object & obj)
{
    // Clear properties
    m_properties.clear();
    m_ownProperties.clear();

    // Copy properties
    for (auto it : obj.m_properties) {
        // Get name and property
        std::string   name = it.first;
        AbstractVar * var  = it.second;

        // Create copy of property
        addProperty(name, std::move(var->clone()));
    }
}


} // namespace cppexpose
