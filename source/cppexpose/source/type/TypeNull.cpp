
#include <cppassist/memory/make_unique.h>

#include <cppexpose/type/TypeNull.h>


namespace cppexpose
{


TypeNull::TypeNull()
{
}

TypeNull::~TypeNull()
{
}

std::unique_ptr<AbstractType> TypeNull::createCopy() const
{
    return cppassist::make_unique<TypeNull>();
}

const AbstractType & TypeNull::type() const
{
    return *this;
}

const AbstractType & TypeNull::elementType() const
{
    return *this;
}

std::string TypeNull::typeName() const
{
    return "undefined";
}

bool TypeNull::isNull() const
{
    return true;
}

bool TypeNull::isType() const
{
    return false;
}

bool TypeNull::isConst() const
{
    return false;
}

bool TypeNull::isArray() const
{
    return false;
}

bool TypeNull::isDynamicArray() const
{
    return false;
}

bool TypeNull::isMap() const
{
    return false;
}

bool TypeNull::isBoolean() const
{
    return false;
}

bool TypeNull::isNumber() const
{
    return false;
}

bool TypeNull::isIntegral() const
{
    return false;
}

bool TypeNull::isUnsigned() const
{
    return false;
}

bool TypeNull::isFloatingPoint() const
{
    return false;
}

bool TypeNull::isString() const
{
    return false;
}

bool TypeNull::hasSymbolicNames() const
{
    return false;
}

std::vector<std::string> TypeNull::symbolicNames() const
{
    static std::vector<std::string> emptyNames;

    return emptyNames;
}


} // namespace cppexpose
