
#include <cppexpose/reflection/AbstractProperty.h>


namespace cppexpose
{


AbstractProperty::AbstractProperty()
: Member("")
{
}

AbstractProperty::AbstractProperty(const std::string & name)
: Member(name)
{
}

AbstractProperty::~AbstractProperty()
{
}


} // namespace cppexpose
