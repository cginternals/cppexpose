
#include <cppexpose/reflection/PropertyGroup.h>

#include <typeinfo>

#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


PropertyGroup::PropertyGroup(const std::string & name)
: Named(name)
{
}

PropertyGroup::~PropertyGroup()
{
}

AbstractTyped * PropertyGroup::clone() const
{
    // [TODO]
    return new PropertyGroup(name());
}

const std::type_info & PropertyGroup::type() const
{
    return typeid(PropertyGroup);
}

std::string PropertyGroup::typeName() const
{
    return "PropertyGroup";
}

bool PropertyGroup::isReadOnly() const
{
    return false;
}

bool PropertyGroup::isComposite() const
{
    return true;
}

size_t PropertyGroup::numSubValues() const
{
    // [TODO]
    return 0;
}

AbstractTyped * PropertyGroup::subValue(size_t)
{
    // [TODO]
    return nullptr;
}

bool PropertyGroup::isEnum() const
{
    return false;
}

bool PropertyGroup::isArray() const
{
    return false;
}

bool PropertyGroup::isVariant() const
{
    return false;
}

bool PropertyGroup::isString() const
{
    return false;
}

bool PropertyGroup::isBool() const
{
    return false;
}

bool PropertyGroup::isNumber() const
{
    return false;
}

bool PropertyGroup::isIntegral() const
{
    return false;
}

bool PropertyGroup::isSignedIntegral() const
{
    return false;
}

bool PropertyGroup::isUnsignedIntegral() const
{
    return false;
}

bool PropertyGroup::isFloatingPoint() const
{
    return false;
}

Variant PropertyGroup::toVariant() const
{
    // [TODO]
    return Variant();
}

bool PropertyGroup::fromVariant(const Variant &)
{
    // [TODO]
    return false;
}

std::string PropertyGroup::toString() const
{
    // [TODO]
    return "";
}

bool PropertyGroup::fromString(const std::string &)
{
    // [TODO]
    return false;
}

bool PropertyGroup::toBool() const
{
    return false;
}

bool PropertyGroup::fromBool(bool)
{
    return false;
}

long long PropertyGroup::toLongLong() const
{
    return 0ll;
}

bool PropertyGroup::fromLongLong(long long)
{
    return false;
}

unsigned long long PropertyGroup::toULongLong() const
{
    return 0ull;
}

bool PropertyGroup::fromULongLong(unsigned long long)
{
    return false;
}

double PropertyGroup::toDouble() const
{
    return 0.0;
}

bool PropertyGroup::fromDouble(double)
{
    return false;
}


} // namespace cppexpose
