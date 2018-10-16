
#pragma once


#include <string>
#include <vector>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractComponent;


/**
*  @brief
*    Represents a dynamic plugin library
*/
class CPPEXPOSE_API PluginLibrary
{
    friend class ComponentManager;


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] filePath
    *    Path to the loaded library
    */
    PluginLibrary(const std::string & filePath);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PluginLibrary();

    /**
    *  @brief
    *    Get path to library file
    *
    *  @return
    *    Path to the loaded library
    */
    const std::string & filePath() const;

    /**
    *  @brief
    *    Check if plugin library is valid
    *
    *  @return
    *    'true' if the plugin has been loaded successfully, else 'false'
    */
    bool isValid() const;

    /**
    *  @brief
    *    Get components that belong to the plugin library
    *
    *  @return
    *    List of components that belong to the plugin library
    */
    const std::vector<AbstractComponent *> & components() const;


protected:
    /**
    *  @brief
    *    Add component to library
    *
    *  @param[in] component
    *    Component (must NOT be null!)
    *
    *  @remarks
    *    As components register themselves automatically, this
    *    function is called by the component manager to remember
    *    what components belong to a plugin library.
    */
    void addComponent(AbstractComponent * component);


protected:
    std::string                      m_filePath;         ///< Path to the loaded library
    void                           * m_handle;           ///< Library handle
    std::vector<AbstractComponent *> m_components;       ///< List of components that belong to the plugin library
};


} // namespace cppexpose
