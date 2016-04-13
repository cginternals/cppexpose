
#include <cppexpose/reflection/Object.h>


namespace cppexpose
{


Object::Object(const std::string & name)
: PropertyGroup(name)
{
}

Object::~Object()
{
}

const std::vector<Function> & Object::functions() const
{
    return m_functions;
}


} // namespace cppexpose
