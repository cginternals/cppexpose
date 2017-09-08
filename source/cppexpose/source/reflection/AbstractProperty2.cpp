
#include <cppexpose/reflection/AbstractProperty2.h>

//#include <cppexpose/reflection/Object.h>


namespace cppexpose
{


AbstractProperty2::AbstractProperty2()
: m_name("")
, m_parent(nullptr)
, m_value(nullptr)
{
}

AbstractProperty2::~AbstractProperty2()
{
    beforeDestroy(this);

    if (m_parent)
    {
        // [TODO]
        // m_parent->removeProperty(this);
    }
}

const std::string & AbstractProperty2::name() const
{
    return m_name;
}

void AbstractProperty2::setName(const std::string & name)
{
    m_name = name;
}

Object * AbstractProperty2::parent() const
{
    return m_parent;
}

bool AbstractProperty2::hasParent() const
{
    return m_parent != nullptr;
}

void AbstractProperty2::initProperty(const std::string & name, Object * parent)
{
    // Store name
    m_name = name;

    // Is not desired as parent->addProperty updates the m_parent but asserts beforehand that this property has no parent set.
    // m_parent = parent;

    // Add property to parent object
    if (parent)
    {
        // [TODO]
//      parent->addProperty(this);
    }
}

void AbstractProperty2::setParent(Object * parent)
{
    m_parent = parent;
}

std::string AbstractProperty2::typeName() const
{
    return m_value->typeName();
}

bool AbstractProperty2::isConst() const
{
    return m_value->isConst();
}

bool AbstractProperty2::isArray() const
{
    return m_value->isArray();
}

bool AbstractProperty2::isDynamicArray() const
{
    return m_value->isDynamicArray();
}

bool AbstractProperty2::isMap() const
{
    return m_value->isMap();
}

bool AbstractProperty2::isBoolean() const
{
    return m_value->isBoolean();
}

bool AbstractProperty2::isNumber() const
{
    return m_value->isNumber();
}

bool AbstractProperty2::isIntegral() const
{
    return m_value->isIntegral();
}

bool AbstractProperty2::isUnsigned() const
{
    return m_value->isUnsigned();
}

bool AbstractProperty2::isFloatingPoint() const
{
    return m_value->isFloatingPoint();
}

bool AbstractProperty2::isString() const
{
    return m_value->isString();
}

const AbstractBaseType & AbstractProperty2::type() const
{
    return m_value->type();
}

std::unique_ptr<AbstractValue> AbstractProperty2::createCopy() const
{
    return m_value->createCopy();
}

std::string AbstractProperty2::toString() const
{
    return m_value->toString();
}

bool AbstractProperty2::fromString(const std::string & value)
{
    return m_value->fromString(value);
}

bool AbstractProperty2::toBool() const
{
    return m_value->toBool();
}

bool AbstractProperty2::fromBool(bool value)
{
    return m_value->fromBool(value);
}

long long AbstractProperty2::toLongLong() const
{
    return m_value->toLongLong();
}

bool AbstractProperty2::fromLongLong(long long value)
{
    return m_value->fromLongLong(value);
}

unsigned long long AbstractProperty2::toULongLong() const
{
    return m_value->toULongLong();
}

bool AbstractProperty2::fromULongLong(unsigned long long value)
{
    return m_value->fromULongLong(value);
}

double AbstractProperty2::toDouble() const
{
    return m_value->toDouble();
}

bool AbstractProperty2::fromDouble(double value)
{
    return m_value->fromDouble(value);
}


} // namespace cppexpose
