
#pragma once


#include <string>

#include <cppexpose/Object.h>
#include <cppexpose/Array.h>
#include <cppexpose/Var.h>

#include <cppexpose-xml/cppexpose-xml_api.h>


namespace cppexpose_xml
{


/**
*  @brief
*    XML element
*/
class CPPEXPOSE_XML_API Element : public cppexpose::Object
{
public:
    cppexpose::Var<std::string> name;     ///< Element name
    cppexpose::Var<std::string> text;     ///< Text content
    cppexpose::Array            children; ///< Array containing the child elements

public:
    /**
    *  @brief
    *    Constructor
    */
    Element();

    /**
    *  @brief
    *    Copy Constructor
    *
    *  @param[in] element
    *    Element that will be copied
    */
    Element(const Element & element);

    /**
    *  @brief
    *    Move Constructor
    *
    *  @param[in] element
    *    Element that will be moved
    */
    Element(Element && element);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Element();

    // Replication
    virtual std::unique_ptr<AbstractVar> clone() const override;
    virtual std::unique_ptr<AbstractVar> move() override;
};


} // namespace cppexpose_xml
