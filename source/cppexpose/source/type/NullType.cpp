
#include <cppassist/memory/make_unique.h>

#include <cppexpose/type/NullType.h>


namespace cppexpose
{


NullType::NullType()
{
}

NullType::~NullType()
{
}

std::unique_ptr<AbstractBaseType> NullType::createCopy() const
{
    return cppassist::make_unique<NullType>();
}

AbstractBaseType & NullType::type()
{
    return *this;
}

AbstractBaseType & NullType::elementType()
{
    return *this;
}

std::string NullType::typeName() const
{
    return "undefined";
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


} // namespace cppexpose
