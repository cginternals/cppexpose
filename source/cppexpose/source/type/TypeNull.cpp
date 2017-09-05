
#include <typeinfo>

#include <cppexpose/type/TypeNull.h>


namespace cppexpose
{


TypeNull::TypeNull()
{
}

TypeNull::~TypeNull()
{
}

const std::type_info & TypeNull::typeInfo() const
{
    return typeid(void);
}

std::string TypeNull::typeName() const
{
    return "undefined";
}

const AbstractType & TypeNull::elementType() const
{
    return *this;
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

bool TypeNull::isType() const
{
    return false;
}


} // namespace cppexpose
