
#include <cppexpose/type/AbstractBaseType.h>


namespace cppexpose
{


AbstractBaseType::AbstractBaseType()
{
}

AbstractBaseType::~AbstractBaseType()
{
}

bool AbstractBaseType::operator==(const AbstractBaseType & type) const
{
    // Compare types by type name
    return typeName() == type.typeName();
}

bool AbstractBaseType::operator!=(const AbstractBaseType & type) const
{
    // Compare types by type name
    return typeName() != type.typeName();
}


} // namespace cppexpose
