
#include <cppexpose/reflection/Method.h>

#include <cppexpose/function/AbstractFunction.h>


namespace cppexpose
{


Method::Method(std::unique_ptr<AbstractFunction> && func, Object * parent)
: Function(std::move(func))
, m_name("")
, m_parent(parent)
{
}

Method::Method(const std::string & name, std::unique_ptr<AbstractFunction> && func, Object * parent)
: Function(std::move(func))
, m_name(name)
, m_parent(parent)
{
}

Method::~Method()
{
}

const std::string & Method::name() const
{
    return m_name;
}

Object * Method::parent() const
{
    return m_parent;
}


} // namespace cppexpose
