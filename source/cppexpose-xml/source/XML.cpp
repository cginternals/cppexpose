
#include <cppexpose-xml/XML.h>

#include <fstream>
#include <sstream>

#include <pugixml/pugixml.hpp>

#include <cppexpose-xml/Element.h>


using namespace cppexpose;


namespace cppexpose_xml
{


Element parseDocument(const pugi::xml_document & document);
Element parseElement(const pugi::xml_node & element);
void saveElement(pugi::xml_node & node, const Element & element);


std::string XML::stringify(const Element & element)
{
    // Create XML document
    pugi::xml_document document;
    saveElement(document, element);

    // Convert to XML
    std::stringstream ss;
    document.print(ss);

    // Output XML
    return ss.str();
}

Element XML::load(const std::string & filename)
{
    // Open XML file
    std::ifstream f(filename);

    // Load XML document
    pugi::xml_document document;
    document.load(f);

    // Parse XML document
    return parseDocument(document);
}

Element XML::parse(const std::string & xml)
{
    // Set XML document
    pugi::xml_document document;
    document.load_string(xml.c_str());

    // Parse XML document
    return parseDocument(document);
}

Element parseDocument(const pugi::xml_document & document)
{
    // Get root element of XML document
    auto root = document.document_element();

    // Parse root element
    return parseElement(root);
}

Element parseElement(const pugi::xml_node & node)
{
    Element element;

    // Set element name
    element.name.setValue(node.name());

    // Process attributes
    for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
    {
        // Get attribute
        auto & attr = *it;

        // Add attribute to element
        std::string name  = attr.name();
        std::string value = attr.value();
        element.createProperty<std::string>(name, value);
    }

    // Process child nodes
    for (auto it = node.begin(); it != node.end(); it++)
    {
        // Get child node
        auto & childNode = *it;

        // Element
        if (childNode.type() == pugi::node_element)
        {
            // Parse child element
            Element child = parseElement(childNode);

            // Add child element
            element.children.push(std::move(child));
        }

        // Text
        else if (childNode.type() == pugi::node_pcdata)
        {
            // Get text
            std::string text = childNode.text().as_string();

            // Create text element
            Element child;
            child.text.setValue(text);

            // Add child element
            element.children.push(std::move(child));
        }

        // CDATA
        else if (childNode.type() == pugi::node_cdata)
        {
            // Get text
            std::string text = childNode.text().as_string();

            // Create text element
            Element child;
            child.text.setValue(text);

            // Add child element
            element.children.push(std::move(child));
        }
    }

    // Return element
    return std::move(element);
}

void saveElement(pugi::xml_node & node, const Element & element)
{
    // Element
    if (!element.name.value().empty()) {
        // Create child node
        pugi::xml_node childNode = node.append_child(element.name.value().c_str());

        // Save attributes
        for (auto it : element.properties()) {
            // Get property
            auto name = it.first;
            auto prop = it.second;

            // Ignore "name", "text", "children", and all functions
            if (name != "name" && name != "text" && name != "children" && prop->type() != VarType::Function) {
                // Add attribute
                auto attr = childNode.append_attribute(name.c_str());
                attr.set_value(prop->toString().c_str());
            }
        }

        // Save child elements
        for (size_t i=0; i<element.children.size(); i++) {
            auto * child = static_cast<const Element *>(element.children.at(i));
            saveElement(childNode, *child);
        }
    }

    // Text
    else if (!element.text.value().empty()) {
        // Create child node
        pugi::xml_node childNode = node.append_child(pugi::node_pcdata);
        childNode.text().set(element.text.value().c_str());
    }
}


} // namespace cppexpose_xml
