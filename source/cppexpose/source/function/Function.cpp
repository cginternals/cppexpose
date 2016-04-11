
#include <cppexpose/function/Function.h>

#include <cppexpose/function/StaticFunction.h>
#include <cppexpose/function/MemberFunction.h>


namespace cppexpose
{


Function::Function(const std::string & name, AbstractFunction * func)
: m_name(name)
, m_func(func)
{
}

Function::Function(const Function & other)
: m_name(other.m_name)
, m_func(other.m_func ? other.m_func->clone() : nullptr)
{
}

Function::~Function()
{
    delete m_func;
}

Function & Function::operator=(const Function & other)
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

std::string Function::name() const
{
    return m_name;
}

Variant Function::call(const std::vector<Variant> & args)
{
    // Call function
    if (m_func) {
        return m_func->call(args);
    }

    // Empty function
    return Variant();
}


} // namespace cppexpose
