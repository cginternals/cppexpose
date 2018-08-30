
#pragma once


#include <string>

#include <cppexpose-xml/cppexpose-xml_api.h>


namespace cppexpose_xml
{


class Element;


/**
*  @brief
*    XML import/export
*/
class CPPEXPOSE_XML_API XML
{
public:
    /**
    *  @brief
    *    Save data to XML
    *
    *  @param[in] root
    *    XML element
    *
    *  @return
    *    XML string
    */
    static std::string stringify(const Element & root);

    /**
    *  @brief
    *    Load XML from file
    *
    *  @param[in] filename
    *    Filename of XML file
    *
    *  @return
    *    Read value, empty on error
    */
    static Element load(const std::string & filename);

    /**
    *  @brief
    *    Parse XML from string
    *
    *  @param[in] xml
    *    XML string
    *
    *  @return
    *    Read value, empty on error
    */
    static Element parse(const std::string & xml);
};


} // namespace cppexpose_xml
