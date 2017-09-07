
#include <cppexpose/type/MetaType.h>

#include <typeinfo>

#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


MetaType::MetaType()
{
}

MetaType::~MetaType()
{
}

std::unique_ptr<AbstractType> MetaType::createCopy() const
{
    return cppassist::make_unique<MetaType>();
}

AbstractType & MetaType::type()
{
    return *this;
}

AbstractType & MetaType::elementType()
{
    return *this;
}

std::string MetaType::typeName() const
{
    return "type";
}

bool MetaType::isNull() const
{
    return false;
}

bool MetaType::isConst() const
{
    return false;
}

bool MetaType::isType() const
{
    return true;
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

bool MetaType::hasSymbolicNames() const
{
    return false;
}

std::vector<std::string> MetaType::symbolicNames() const
{
    static std::vector<std::string> emptyNames;

    return emptyNames;
}


} // namespace cppexpose
