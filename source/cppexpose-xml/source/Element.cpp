
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

Element::Element(const Element & element)
: cppexpose::Object()
, name(this, "name", element.name.value())
, text(this, "text", element.text.value())
, children(this, "children")
{
    // Copy child elements
    for (size_t i=0; i<element.children.size(); i++) {
        const AbstractVar * child = element.children.at(i);
        children.push(std::move(child->clone()));
    }
}

Element::Element(Element && element)
: cppexpose::Object()
, name(this, "name", element.name.value())
, text(this, "text", element.text.value())
, children(this, "children")
{
    // Move child elements
    for (size_t i=0; i<element.children.size(); i++) {
        auto * child = static_cast<Element *>(element.children.at(i));
        children.push(std::move(child->move()));
    }
}

Element::~Element()
{
}

std::unique_ptr<AbstractVar> Element::clone() const
{
    return std::unique_ptr<Element>(new Element(*this));
}

std::unique_ptr<AbstractVar> Element::move()
{
    return cppassist::make_unique<Element>(std::move(*this));
}


} // namespace cppexpose_xml
