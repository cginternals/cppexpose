
#include <cppexpose/function/Function.h>

#include <cppexpose/function/StaticFunction.h>
#include <cppexpose/function/MemberFunction.h>


namespace cppexpose
{


Function::Function(AbstractFunction * func)
: m_func(func)
{
}

Function::Function(const Function & other)
: m_func(other.m_func ? other.m_func->clone() : nullptr)
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
    m_func = other.m_func ? other.m_func->clone() : nullptr;
    return *this;
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
