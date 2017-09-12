
#include <cppexpose/type/MetaType.h>

#include <typeinfo>

#include <cppassist/memory/make_unique.h>
#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


MetaType::MetaType()
{
}

MetaType::~MetaType()
{
}

std::shared_ptr<AbstractBaseType> MetaType::createCopy() const
{
    return std::shared_ptr<AbstractBaseType>(new MetaType);
}

bool MetaType::hasElementType() const
{
    return false;
}

std::shared_ptr<AbstractBaseType> MetaType::elementType()
{
    return nullptr;
}

const std::string & MetaType::typeName() const
{
    static const auto name = std::string("type");

    return name;
}

bool MetaType::isNull() const
{
    return false;
}

bool MetaType::isType() const
{
    return true;
}

bool MetaType::isConst() const
{
    return false;
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

Variant MetaType::minimum() const
{
    return Variant();
}

void MetaType::setMinimum(const Variant &)
{
}

Variant MetaType::maximum() const
{
    return Variant();
}

void MetaType::setMaximum(const Variant &)
{
}


} // namespace cppexpose
