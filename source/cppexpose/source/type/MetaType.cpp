
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

std::unique_ptr<AbstractBaseType> MetaType::createCopy() const
{
    return cppassist::make_unique<MetaType>();
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

bool MetaType::hasElementType() const
{
    return false;
}

std::shared_ptr<AbstractBaseType> MetaType::elementType()
{
    return nullptr;
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
