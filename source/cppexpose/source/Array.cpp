
#include <cppexpose/Array.h>

#include <algorithm>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/Object.h>
#include <cppexpose/Variant.h>
#include <cppexpose/JSON.h>


namespace cppexpose
{


Array Array::create()
{
    return std::move(Array());
}

Array::Array()
{
}

Array::Array(PropertyContainer * parent, const std::string & name)
{
    registerProperty(parent, name);
}

Array::Array(const Array & arr)
: PropertyContainer()
{
    copyFromArray(arr);
}

Array::Array(Array && arr)
: PropertyContainer()
{
    // Move properties
    for (AbstractVar * var : arr.m_properties) {
        // Check if property is owned by the array
        auto it = std::find_if(arr.m_ownProperties.begin(), arr.m_ownProperties.end(), [var] (const std::unique_ptr<AbstractVar> & ptr)
        {
            return ptr.get() == var;
        });

        if (it != arr.m_ownProperties.end()) {
            // Move unique_ptr directly
            push(std::move(*it));
        } else {
            // Move property by function call
            push(var->move());
        }
    }

    // Clear properties on source object
    arr.clear();
}

Array::~Array()
{
}

Array & Array::operator =(const AbstractVar & var)
{
    fromVar(var);
    return *this;
}

bool Array::empty() const
{
    return m_properties.empty();
}

void Array::clear()
{
    // Clear properties
    m_properties.clear();
    m_ownProperties.clear();
}

size_t Array::size() const
{
    return m_properties.size();
}

const AbstractVar * Array::at(size_t index) const
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

AbstractVar * Array::at(size_t index)
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

AbstractVar * Array::push(AbstractVar * property)
{
    // Reject properties that already have a parent.
    if (!property || property->parent() != nullptr)
    {
        return nullptr;
    }

    // Set parent
    property->setParent(this);

    // Invoke callback
    auto newIndex = m_properties.size();
    beforeAdd(newIndex, property);

    // Add property
    m_properties.push_back(property);

    // Invoke callback
    afterAdd(newIndex, property);

    // Success
    return property;
}

AbstractVar * Array::push(AbstractVar && property)
{
    // Move property to a new instance
    auto movedProperty = property.move();

    // Add property
    const auto propertyPtr = push(movedProperty.get());
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

AbstractVar * Array::push(std::unique_ptr<AbstractVar> && property)
{
    // Add property
    const auto propertyPtr = push(property.get());
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

bool Array::remove(AbstractVar * property)
{
    // Reject properties that are not part of the array
    if (!property || property->parent() != this)
    {
        return false;
    }

    // Find property in array
    auto it = std::find(m_properties.begin(), m_properties.end(), property);

    // Abort if property is not part of the array
    if (it == m_properties.end())
    {
        return false;
    }

    // Invoke callback
    size_t index = std::distance(m_properties.begin(), it);
    beforeRemove(index, property);

    // Remove property from array
    m_properties.erase(it);

    // Reset property parent
    if (property->parent() == this) {
        property->setParent(nullptr);
    }

    // Invoke callback
    afterRemove(index, property);

    // Check if property is owned by the array
    auto it2 = std::find_if(m_ownProperties.begin(), m_ownProperties.end(), [property] (const std::unique_ptr<AbstractVar> & managedProperty)
    {
        return managedProperty.get() == property;
    });

    // If yet, remove from managed list (delete property)
    if (it2 != m_ownProperties.end())
    {
        m_ownProperties.erase(it2);
    }

    // Success
    return true;
}

const AbstractVar * Array::innermost() const
{
    return this;
}

AbstractVar * Array::innermost()
{
    return this;
}

std::unique_ptr<AbstractVar> Array::clone() const
{
    return std::unique_ptr<AbstractVar>(new Array(*this));
}

std::unique_ptr<AbstractVar> Array::move()
{
    return cppassist::make_unique<Array>(std::move(*this));
}

VarType Array::type() const
{
    return VarType::Array;
}

std::string Array::typeName() const
{
    return "Array";
}

bool Array::isNull() const
{
    return false;
}

bool Array::isBool() const
{
    return false;
}

bool Array::isNumber() const
{
    return false;
}

bool Array::isIntegral() const
{
    return false;
}

bool Array::isSignedIntegral() const
{
    return false;
}

bool Array::isFloatingPoint() const
{
    return false;
}

bool Array::isEnum() const
{
    return false;
}

bool Array::isString() const
{
    return false;
}

bool Array::isExternal() const
{
    return false;
}

bool Array::isPointer() const
{
    return false;
}

bool Array::isObject() const
{
    return false;
}

bool Array::isObjectPointer() const
{
    return false;
}

bool Array::isArray() const
{
    return true;
}

bool Array::isArrayPointer() const
{
    return false;
}

bool Array::isFunction() const
{
    return false;
}

bool Array::isConst() const
{
    return false;
}

Variant Array::minimumValue() const
{
    return Variant();
}

Variant Array::maximumValue() const
{
    return Variant();
}

bool Array::canConvertToString() const
{
    return true;
}

std::string Array::toString() const
{
    std::stringstream ss;

    // Begin array
    ss << "[";

    // Iterate over properties
    bool first = true;
    for (auto * var : m_properties) {
        // Ignore certain types of var
        if (var->isNull() || var->isFunction()) {
            continue;
        }

        // Output comma between two properties
        if (!first) {
            ss << ", ";
        } else first = false;

        // Output property value
        if (var->isString()) ss << "\"";
        ss << var->toString();
        if (var->isString()) ss << "\"";
    }

    // End array
    ss << "]";

    // Return string
    return ss.str();
}

bool Array::canConvertToBool() const
{
    return false;
}

bool Array::toBool() const
{
    return false;
}

bool Array::canConvertToLongLong() const
{
    return false;
}

long long Array::toLongLong() const
{
    return 0l;
}

bool Array::canConvertToULongLong() const
{
    return false;
}

unsigned long long Array::toULongLong() const
{
    return 0ul;
}

bool Array::canConvertToDouble() const
{
    return false;
}

double Array::toDouble() const
{
    return 0.0;
}

bool Array::canConvertToObject() const
{
    return false;
}

Object Array::toObject() const
{
    return Object();
}

bool Array::canConvertToArray() const
{
    return true;
}

Array Array::toArray() const
{
    return *this;
}

bool Array::canConvertFromVar(const AbstractVar & value)
{
    return (value.isArray() || value.canConvertToArray() || value.isString() || value.canConvertToString());
}

void Array::fromVar(const AbstractVar & value)
{
    if (value.isArray()) {
        const Array & arr = static_cast<const Array &>(value);
        copyFromArray(arr);
    } else if (value.canConvertToArray()) {
        Array arr = value.toArray();
        copyFromArray(arr);
    } else if (value.isString() || value.canConvertToString()) {
        JSON::parse(*this, value.toString());
    }
}

const Object * Array::asObject() const
{
    return nullptr;
}

const Array * Array::asArray() const
{
    return this;
}

void Array::copyFromArray(const Array & arr)
{
    // Clear properties
    clear();

    // Copy properties
    for (auto * var : arr.m_properties) {
        // Create copy of property
        push(std::move(var->clone()));
    }
}


} // namespace cppexpose
