
#include <cppexpose/reflection/Member.h>


namespace cppexpose
{


Member::Member()
: m_name("")
{
}

Member::Member(const std::string & name)
: m_name(name)
{
}

Member::~Member()
{
}

std::string Member::name() const
{
    return m_name;
}


} // namespace cppexpose
