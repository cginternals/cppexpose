
#pragma once


#include <string>

#include <cpplocate/ModuleInfo.h>

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
    *
    *  @param[in] name
    *    Component name
    *  @param[in] description
    *    Component description
    *  @param[in] type
    *    Component type
    *  @param[in] subtype
    *    Component sub-type (user-defined)
    *  @param[in] annotations
    *    Component annotations (user-defined)
    *  @param[in] vendor
    *    Vendor name
    *  @param[in] version
    *    Component version
    */
    AbstractComponent(
      const std::string & name
    , const std::string & description
    , const std::string & type
    , const std::string & subtype
    , const std::string & annotations
    , const std::string & vendor
    , const std::string & version);

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
    *    Component sub-type
    *
    *  @remarks
    *    The sub-type can be chosen arbitrarily by the using application
    *    for example to order plugins into additional categories.
    *    It is empty by default.
    */
    const char * subtype() const;

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

    /**
    *  @brief
    *    Get module info
    *
    *  @return
    *    Module information, read from modinfo file (if present)
    *
    *  @remarks
    *    To set this information, create a file named <libname>.modinfo in the same
    *    directory that contains your plugin libraries and define all necessary information.
    *    (libmyplugin.so -> libmyplugin.modinfo, or myplugin.dll -> myplugin.modinfo).
    *    For example, you should define the data path relative to that directory:
    *      { "dataPath": "${ModulePath}/../data" }
    */
    const cpplocate::ModuleInfo & moduleInfo() const;

    /**
    *  @brief
    *    Set module info
    *
    *  @param[in] modInfo
    *    Module information found next to the plugin library
    *
    *  @remarks
    *    Do not call this function directly, let ComponentManager do the magic
    */
    void setModuleInfo(const cpplocate::ModuleInfo & moduleInfo);


protected:
    std::string           m_name;         ///< Component name
    std::string           m_description;  ///< Component description
    std::string           m_type;         ///< Component type
    std::string           m_subtype;      ///< Component sub-type
    std::string           m_annotations;  ///< Component annotations
    std::string           m_vendor;       ///< Vendor name
    std::string           m_version;      ///< Component version
    cpplocate::ModuleInfo m_moduleInfo;   ///< Module information for the plugin library
};


} // namespace cppexpose
