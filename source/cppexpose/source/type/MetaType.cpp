
#include <cppexpose/type/MetaType.h>

#include <typeinfo>


namespace cppexpose
{


MetaType::MetaType()
{
}

MetaType::~MetaType()
{
}

const AbstractType & MetaType::type() const
{
    return *this;
}

std::string MetaType::typeName() const
{
    return "type";
}

bool MetaType::isArray() const
{
    return false;
}

bool MetaType::isDynamicArray() const
{
    return false;
}

bool MetaType::isMap() const
{
    return false;
}

bool MetaType::isBoolean() const
{
    return false;
}

bool MetaType::isNumber() const
{
    return true;
}

bool MetaType::isIntegral() const
{
    return true;
}

bool MetaType::isUnsigned() const
{
    return false;
}

bool MetaType::isFloatingPoint() const
{
    return false;
}

bool MetaType::isString() const
{
    return false;
}

bool MetaType::isType() const
{
    return true;
}


} // namespace cppexpose
