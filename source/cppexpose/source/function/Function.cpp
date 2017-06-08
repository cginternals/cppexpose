
#include <cppexpose/function/Function.h>

#include <cppexpose/function/StaticFunction.h>
#include <cppexpose/function/MemberFunction.h>


namespace cppexpose
{


Function::Function(std::unique_ptr<AbstractFunction> && func)
: m_func(std::move(func))
{
}

Function::Function(const Function & other)
: m_func(other.m_func ? other.m_func->clone() : nullptr)
{
}

Function::~Function()
{
}

Function & Function::operator=(const Function & other)
{
    // Copy function
    m_func = other.m_func ? other.m_func->clone() : nullptr;
    return *this;
}

bool Function::isEmpty() const
{
    return m_func == nullptr;
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
