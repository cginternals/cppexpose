
#include <cppexpose-xml/XML.h>

#include <fstream>
#include <iostream>

#include <pugixml/pugixml.hpp>

#include <cppexpose-xml/Element.h>


namespace cppexpose_xml
{


Element parseDocument(const pugi::xml_document & document);
Element parseElement(const pugi::xml_node & element);


std::string XML::stringify(const Element &)
{
    // [TODO]
    return "";
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


} // namespace cppexpose_xml
