
#include <cppexpose/reflection/Object.h>


namespace cppexpose
{


Object::Object(const std::string & name, PropertyGroup * parent)
: PropertyGroup(name, parent)
{
}

Object::~Object()
{
}

const std::vector<Method> & Object::functions() const
{
    return m_functions;
}


} // namespace cppexpose
