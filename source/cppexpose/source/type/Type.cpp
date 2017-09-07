
#include <cppexpose/type/Type.h>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/type/TypeNull.h>
#include <cppexpose/type/TypedType.h>


namespace cppexpose
{


Type::Type()
: m_type(new TypeNull())
{
}

Type::Type(std::unique_ptr<AbstractType> && basicType)
: m_type(std::move(basicType))
{
}

Type::Type(const Type & type)
: m_type(type.m_type->createCopy())
{
}

Type::~Type()
{
}

Type & Type::operator=(const Type & type)
{
    m_type = type.m_type->createCopy();
    return *this;
}

const Type & Type::type() const
{
    return *this;
}

Type & Type::type()
{
    return *this;
}

const Type & Type::elementType() const
{
    static Type elementType(m_type->elementType().createCopy());
    return elementType;
}

Type & Type::elementType()
{
    static Type elementType(m_type->elementType().createCopy());
    return elementType;
}

std::string Type::typeName() const
{
    return m_type->typeName();
}

bool Type::isNull() const
{
    return m_type->isNull();
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

bool Type::isType() const
{
    return m_type->isType();
}

bool Type::hasSymbolicNames() const
{
    return m_type->hasSymbolicNames();
}

std::vector<std::string> Type::symbolicNames() const
{
    return m_type->symbolicNames();
}


} // namespace cppexpose
