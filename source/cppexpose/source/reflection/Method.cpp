
#include <cppexpose/reflection/Method.h>

#include <cppexpose/function/AbstractFunction.h>


namespace cppexpose
{


Method::Method(const std::string & name, AbstractFunction * func)
: Function(func)
, Member(name)
{
}

Method::Method(const Method & other)
: Function(static_cast<const Function &>(other))
, Member(other.m_name)
{
}

Method::~Method()
{
}

Method & Method::operator=(const Method & other)
{
    // Delete old function
    if (m_func) {
        delete m_func;
    }

    // Copy function
    m_name = other.m_name;
    m_func = other.m_func ? other.m_func->clone() : nullptr;
    return *this;
}


} // namespace cppexpose
