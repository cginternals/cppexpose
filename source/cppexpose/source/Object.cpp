
#include <cppexpose/Object.h>

#include <algorithm>
#include <sstream>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/Array.h>
#include <cppexpose/Variant.h>
#include <cppexpose/AbstractVar.h>
#include <cppexpose/JSON.h>


namespace cppexpose
{


Object Object::create()
{
    return std::move(Object());
}

Object::Object()
{
    // Register scripting functions
    registerFunctions();
}

Object::Object(PropertyContainer * parent, const std::string & name)
{
    // Register property at parent
    registerProperty(parent, name);

    // Register scripting functions
    registerFunctions();
}

Object::Object(const Object & obj)
: PropertyContainer()
{
    // Copy properties
    copyFromObject(obj);

    // Register scripting functions
    registerFunctions();
}

Object::Object(Object && obj)
: PropertyContainer()
{
    // Move properties
    for (auto it : obj.m_properties) {
        // Get name and property
        std::string name = it.first;
        AbstractVar * var = it.second;

        // Do not copy functions, as they may be dependent on the instance
        if (var->type() == VarType::Function) {
            continue;
        }

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
    obj.clear();

    // Register scripting functions
    registerFunctions();
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

void Object::clear()
{
    // Clear properties
    m_properties.clear();
    m_ownProperties.clear();

    // Clear signals
    m_signals.clear();
    m_ownSignals.clear();
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
    // Reject property if name is already taken
    if (!property || this->propertyExists(name))
    {
        return nullptr;
    }

    // Set parent
    property->setParent(this);

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
    // Check property
    if (!property)
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
    if (property->parent() == this) {
        property->setParent(nullptr);
    }

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

const Function * Object::function(const std::string & name) const
{
    // Get property
    auto * prop = property(name);
    if (!prop) {
        return nullptr;
    }

    // Check if it is a function
    if (prop->type() != VarType::Function) {
        return nullptr;
    }

    // Get pointer to function
    auto * funcProp = prop->asTyped<const Var<Function> *>();
    return funcProp->get();
}

Function * Object::function(const std::string & name)
{
    // Get property
    auto * prop = property(name);
    if (!prop) {
        return nullptr;
    }

    // Check if it is a function
    if (prop->type() != VarType::Function) {
        return nullptr;
    }

    // Get pointer to function
    auto * funcProp = prop->asTyped<Var<Function> *>();
    return funcProp->get();
}

const std::unordered_map<std::string, AbstractSignal *> & Object::signals() const
{
    return m_signals;
}

bool Object::signalExists(const std::string & name) const
{
    return m_signals.find(name) != m_signals.end();
}

const AbstractSignal * Object::signal(const std::string & name) const
{
    const AbstractSignal * signal = nullptr;

    // Find signal
    const auto it = m_signals.find(name);
    if (it != m_signals.end())
    {
        signal = it->second;
    }

    // Return signal if found
    return signal;
}

AbstractSignal * Object::signal(const std::string & name)
{
    AbstractSignal * signal = nullptr;

    // Find signal
    const auto it = m_signals.find(name);
    if (it != m_signals.end())
    {
        signal = it->second;
    }

    // Return signal if found
    return signal;
}

AbstractSignal * Object::addSignal(const std::string & name, AbstractSignal * signal)
{
    // Reject signal if name is already taken
    if (!signal || this->signalExists(name))
    {
        return nullptr;
    }

    // Add signal
    m_signals.insert(std::make_pair(name, signal));

    // Success
    return signal;
}

AbstractSignal * Object::addSignal(const std::string & name, std::unique_ptr<AbstractSignal> && signal)
{
    // Add signal
    const auto signalPtr = addSignal(name, signal.get());
    if (signalPtr)
    {
        // Manage signal
        m_ownSignals[name] = std::move(signal);

        // Return signal
        return signalPtr;
    }

    // Failed
    return nullptr;
}

bool Object::removeSignal(AbstractSignal * signal)
{
    // Check signal
    if (!signal) {
        return false;
    }

    // Find signal in object
    auto it = std::find_if(m_signals.begin(), m_signals.end(), [signal] (const std::pair<std::string, AbstractSignal *> & pair)
    {
        return pair.second == signal;
    });

    // Abort if signal is not part of the object
    if (it == m_signals.end())
    {
        return false;
    }

    // Get signal name
    std::string name = it->first;

    // Remove signal from object
    m_signals.erase(it);

    // Check if signal is owned by the object
    // If yes, remove from managed list (delete signal)
    auto it2 = m_signals.find(name);
    if (it2 != m_signals.end())
    {
        m_signals.erase(it2);
    }

    // Success
    return true;
}

const AbstractVar * Object::innermost() const
{
    return this;
}

AbstractVar * Object::innermost()
{
    return this;
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

std::string Object::typeName() const
{
    return "Object";
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
    return (value.isObject() || value.canConvertToObject() || value.isString() || value.canConvertToString());
}

void Object::fromVar(const AbstractVar & value)
{
    if (value.isObject()) {
        const Object & obj = static_cast<const Object &>(value);
        copyFromObject(obj);
    } else if (value.canConvertToObject()) {
        Object obj = value.toObject();
        copyFromObject(obj);
    } else if (value.isString() || value.canConvertToString()) {
        JSON::parse(*this, value.toString());
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
    clear();

    // Copy properties
    for (auto it : obj.m_properties) {
        // Get name and property
        std::string   name = it.first;
        AbstractVar * var  = it.second;

        // Do not copy functions, as they are dependent on the instance
        if (var->type() == VarType::Function) {
            continue;
        }

        // Create copy of property
        addProperty(name, std::move(var->clone()));
    }
}

cppexpose::Variant Object::scr_signals()
{
    // Get list of signals
    Array names;
    for (auto it : m_signals) {
        names.push(Variant(it.first));
    }

    // Return list
    return std::move(names);
}

void Object::scr_connect(const std::string & name, const cppexpose::Function & func)
{
    // Get signal
    auto * signal = this->signal(name);
    if (!signal) return;

    // Connect signal to function
    Function function = func;
    signal->connect(function);
}

void Object::registerFunctions()
{
    addFunction("signals", this, &Object::scr_signals);
    addFunction("connect", this, &Object::scr_connect);
}


} // namespace cppexpose
