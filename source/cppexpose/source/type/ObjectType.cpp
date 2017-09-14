
#include <cppexpose/type/ObjectType.h>

#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


ObjectType::ObjectType()
{
}

ObjectType::~ObjectType()
{
}

std::shared_ptr<AbstractBaseType> ObjectType::createCopy() const
{
    return std::shared_ptr<AbstractBaseType>(new ObjectType);
}

bool ObjectType::hasElementType() const
{
    return false;
}

std::shared_ptr<AbstractBaseType> ObjectType::elementType()
{
    return nullptr;
}

const std::string & ObjectType::typeName() const
{
    static const auto name = std::string("object");

    return name;
}

bool ObjectType::isNull() const
{
    return false;
}

bool ObjectType::isType() const
{
    return false;
}

bool ObjectType::isConst() const
{
    return false;
}

bool ObjectType::isArray() const
{
    return false;
}

bool ObjectType::isDynamicArray() const
{
    return false;
}

bool ObjectType::isMap() const
{
    return false;
}

bool ObjectType::isBoolean() const
{
    return false;
}

bool ObjectType::isNumber() const
{
    return false;
}

bool ObjectType::isIntegral() const
{
    return false;
}

bool ObjectType::isUnsigned() const
{
    return false;
}

bool ObjectType::isFloatingPoint() const
{
    return false;
}

bool ObjectType::isString() const
{
    return false;
}

bool ObjectType::hasSymbolicNames() const
{
    return false;
}

std::vector<std::string> ObjectType::symbolicNames() const
{
    static std::vector<std::string> emptyNames;

    return emptyNames;
}

Variant ObjectType::minimum() const
{
    return Variant();
}

void ObjectType::setMinimum(const Variant &)
{
}

Variant ObjectType::maximum() const
{
    return Variant();
}

void ObjectType::setMaximum(const Variant &)
{
}


} // namespace cppexpose
