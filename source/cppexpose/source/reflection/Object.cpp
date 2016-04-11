
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


} // namespace cppexpose
