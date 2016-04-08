
#include <cppexpose/reflection/Named.h>


namespace cppexpose
{


Named::Named(const std::string & name)
: m_name(name)
{
}

Named::~Named()
{
}

std::string Named::name() const
{
    return m_name;
}


} // namespace cppexpose
