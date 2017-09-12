
#include <cppexpose/type/type_system.h>

#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


NullType::NullType()
{
}

NullType::~NullType()
{
}

std::shared_ptr<AbstractBaseType> NullType::createCopy() const
{
    return std::shared_ptr<AbstractBaseType>(new NullType);
}

bool NullType::hasElementType() const
{
    return false;
}

std::shared_ptr<AbstractBaseType> NullType::elementType()
{
    return nullptr;
}

const std::string & NullType::typeName() const
{
    static const auto name = std::string("undefined");

    return name;
}

bool NullType::isNull() const
{
    return true;
}

bool NullType::isType() const
{
    return false;
}

bool NullType::isConst() const
{
    return false;
}

bool NullType::isArray() const
{
    return false;
}

bool NullType::isDynamicArray() const
{
    return false;
}

bool NullType::isMap() const
{
    return false;
}

bool NullType::isBoolean() const
{
    return false;
}

bool NullType::isNumber() const
{
    return false;
}

bool NullType::isIntegral() const
{
    return false;
}

bool NullType::isUnsigned() const
{
    return false;
}

bool NullType::isFloatingPoint() const
{
    return false;
}

bool NullType::isString() const
{
    return false;
}

bool NullType::hasSymbolicNames() const
{
    return false;
}

std::vector<std::string> NullType::symbolicNames() const
{
    static std::vector<std::string> emptyNames;

    return emptyNames;
}

Variant NullType::minimum() const
{
    return Variant();
}

void NullType::setMinimum(const Variant &)
{
}

Variant NullType::maximum() const
{
    return Variant();
}

void NullType::setMaximum(const Variant &)
{
}


} // namespace cppexpose
