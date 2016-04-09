
#include <cppexpose/reflection/AbstractProperty.h>


namespace cppexpose
{


AbstractProperty::AbstractProperty()
: m_name("")
{
}

AbstractProperty::AbstractProperty(const std::string & name)
: m_name(name)
{
}

AbstractProperty::~AbstractProperty()
{
}

std::string AbstractProperty::name() const
{
    return m_name;
}


} // namespace cppexpose
