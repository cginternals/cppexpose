
#include <cppexpose-xml/Element.h>


using namespace cppassist;
using namespace cppexpose;


namespace cppexpose_xml
{


Element::Element()
: name(this, "name")
, text(this, "text")
, children(this, "children")
{
}

Element::~Element()
{
}


} // namespace cppexpose_xml
