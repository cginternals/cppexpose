
#include <cppexpose/function/AbstractFunction.h>


namespace cppexpose
{


AbstractFunction::AbstractFunction(const std::string & name)
: m_name(name)
{
}

AbstractFunction::~AbstractFunction()
{
}

std::string AbstractFunction::name() const
{
    return m_name;
}


} // namespace cppexpose
