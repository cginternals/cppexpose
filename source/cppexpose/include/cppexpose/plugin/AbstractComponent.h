
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class for components
*/
class CPPEXPOSE_API AbstractComponent
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractComponent();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractComponent();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Component name
    */
    const char * name() const;

    /**
    *  @brief
    *    Get description
    *
    *  @return
    *    Component description
    */
    const char * description() const;

    /**
    *  @brief
    *    Get type
    *
    *  @return
    *    Component type
    */
    const char * type() const;

    /**
    *  @brief
    *    Get sub-type
    *
    *  @return
    *    Component tags (user-defined, space-separated)
    *
    *  @remarks
    *    Tags can be chosen arbitrarily by the using application,
    *    for example to order plugins into additional categories.
    *    Tags are empty by default.
    */
    const char * tags() const;

    /**
    *  @brief
    *    Get icon
    *
    *  @return
    *    Icon name or ID
    *
    *  @remarks
    *    The icon field can point to a file name or ID that is used to
    *    display an icon for the component. The actual content is application
    *    specific and not defined by cppexpose.
    */
    const char * icon() const;

    /**
    *  @brief
    *    Get annotations
    *
    *  @return
    *    Component annotations
    *
    *  @remarks
    *    Annotations can be used to provide additional machine-readable
    *    information about the component. The syntax and semantics for
    *    annotations are not defined by cppexpose and can be chosen freely
    *    by the systems that use cppexpose. By default, annotations are empty.
    */
    const char * annotations() const;

    /**
    *  @brief
    *    Get vendor
    *
    *  @return
    *    Vendor name
    */
    const char * vendor() const;

    /**
    *  @brief
    *    Get version
    *
    *  @return
    *    Component version
    */
    const char * version() const;


protected:
    std::string m_name;         ///< Component name
    std::string m_description;  ///< Component description
    std::string m_type;         ///< Component type
    std::string m_tags;         ///< Component tags (user-defined, space-separated)
    std::string m_icon;         ///< Icon name or ID
    std::string m_annotations;  ///< Component annotations
    std::string m_vendor;       ///< Vendor name
    std::string m_version;      ///< Component version
};


} // namespace cppexpose
