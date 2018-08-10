
#include <cppexpose/expose/Array.h>

#include <algorithm>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Variant.h>


namespace cppexpose
{


std::unique_ptr<Array> Array::create()
{
    return cppassist::make_unique<Array>();
}

Array::Array()
{
}

Array::Array(const Array & arr)
: PropertyContainer()
{
    copyFromArray(arr);
}

Array::Array(const std::string & name, PropertyContainer * parent)
{
    registerProperty(name, parent);
}

Array::~Array()
{
}

bool Array::empty() const
{
    return m_properties.empty();
}

size_t Array::size() const
{
    return m_properties.size();
}

const AbstractProperty * Array::at(size_t index) const
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

AbstractProperty * Array::at(size_t index)
{
    if (index < m_properties.size()) {
        return m_properties[index];
    }

    return nullptr;
}

AbstractProperty * Array::push(AbstractProperty * property)
{
    // Reject properties that already have a parent.
    if (!property || property->parent() != nullptr)
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
    m_properties.push_back(property);

    // Invoke callback
    // [TODO]
//  afterAdd(newIndex, property);

    // Success
    return property;
}

AbstractProperty * Array::push(std::unique_ptr<AbstractProperty> && property)
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

bool Array::remove(AbstractProperty * property)
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
    // [TODO]
//  size_t index = std::distance(m_properties.begin(), it);
//  beforeRemove(index, property);

    // Remove property from array
    m_properties.erase(it);

    // Reset property parent
    // [TODO]
//  property->setParent(nullptr);

    // Invoke callback
    // [TODO]
//  afterRemove(index, property);

    // Check if property is owned by the array
    auto it2 = std::find_if(m_ownProperties.begin(), m_ownProperties.end(), [property] (const std::unique_ptr<AbstractProperty> & managedProperty)
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

AbstractVar * Array::clone() const
{
    return new Array(*this);
}

VarType Array::type() const
{
    return VarType::Array;
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

bool Array::isArray() const
{
    return true;
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
    // [TODO]
    return "";
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
    return (value.isArray() || value.canConvertToArray());
}

void Array::fromVar(const AbstractVar & value)
{
    if (value.isArray()) {
        const Array & arr = static_cast<const Array &>(value);
        copyFromArray(arr);
    } else if (value.canConvertToArray()) {
        Array arr = value.toArray();
        copyFromArray(arr);
    }
}

const Array * Array::asArray() const
{
    return this;
}

Array * Array::asArray()
{
    return this;
}

void Array::copyFromArray(const Array &)
{
    // [TODO]
}


} // namespace cppexpose
