
#include <cppexpose/type/Type.h>

#include <cppexpose/type/NullType.h>
#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


Type::Type()
: m_type(new NullType())
{
}

Type::Type(const std::shared_ptr<AbstractBaseType> & basicType)
: m_type(basicType)
{
}

Type::Type(const Type & type)
: m_type(type.m_type)
{
}

Type::~Type()
{
}

Type & Type::operator=(const Type & type)
{
    m_type = type.m_type;
    m_elementType.reset();

    return *this;
}

bool Type::operator==(const Type & type) const
{
    return *type.baseType() == *m_type.get();
}

bool Type::operator!=(const Type & type) const
{
    return *type.baseType() != *m_type.get();
}

const Type & Type::type() const
{
    return *this;
}

Type & Type::type()
{
    return *this;
}

const AbstractBaseType * Type::baseType() const
{
    return m_type.get();
}

AbstractBaseType * Type::baseType()
{
    return m_type.get();
}

const Type & Type::elementType() const
{
    // Check if type has an element type
    if (ensureElementType())
    {
        // Return element type
        return *m_elementType.get();
    }

    // No element type
    return *this;
}

Type & Type::elementType()
{
    // Check if type has an element type
    if (ensureElementType())
    {
        // Return element type
        return *m_elementType.get();
    }

    // No element type
    return *this;
}

const std::string & Type::typeName() const
{
    return m_type->typeName();
}

bool Type::isNull() const
{
    return m_type->isNull();
}

bool Type::isType() const
{
    return m_type->isType();
}

bool Type::isConst() const
{
    return m_type->isConst();
}

bool Type::isArray() const
{
    return m_type->isArray();
}

bool Type::isDynamicArray() const
{
    return m_type->isDynamicArray();
}

bool Type::isMap() const
{
    return m_type->isMap();
}

bool Type::isBoolean() const
{
    return m_type->isBoolean();
}

bool Type::isNumber() const
{
    return m_type->isNumber();
}

bool Type::isIntegral() const
{
    return m_type->isIntegral();
}

bool Type::isUnsigned() const
{
    return m_type->isUnsigned();
}

bool Type::isFloatingPoint() const
{
    return m_type->isFloatingPoint();
}

bool Type::isString() const
{
    return m_type->isString();
}

bool Type::hasSymbolicNames() const
{
    return m_type->hasSymbolicNames();
}

std::vector<std::string> Type::symbolicNames() const
{
    return m_type->symbolicNames();
}

Variant Type::minimum() const
{
    return m_type->minimum();
}

void Type::setMinimum(const Variant & value)
{
    makeUnique();

    m_type->setMinimum(value);
}

Variant Type::maximum() const
{
    return m_type->maximum();
}

void Type::setMaximum(const Variant & value)
{
    makeUnique();

    m_type->setMaximum(value);
}

void Type::makeUnique()
{
    // Return if type is already exclusively used
    if (m_type.use_count() == 1)
    {
        return;
    }

    // Create copy otherwise
    m_type = m_type->createCopy();
    m_elementType.reset();
}

bool Type::ensureElementType() const
{
    // Check if the element type has already been created
    if (!m_elementType)
    {
        return true;
    }

    // No. Try to create it.
    std::shared_ptr<AbstractBaseType> elementType = m_type->elementType();

    // Check if type has an element type
    if (!elementType)
    {
        // No element type defined
        return false;
    }

    // Create wrapper for element type
    m_elementType.reset(new Type(elementType));
    return true;
}


} // namespace cppexpose
