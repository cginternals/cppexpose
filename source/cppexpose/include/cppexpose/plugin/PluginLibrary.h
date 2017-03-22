
#pragma once


#include <vector>
#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractComponent;


/**
*  @brief
*    Function to get information about a plugin library
*/
using GetPluginInfoPtr = const char * (*)();

/**
*  @brief
*    Function for initializing a plugin library
*/
using InitPluginPtr = void (*)();

/**
*  @brief
*    Function for de-initializing a plugin library
*/
using DeInitPluginPtr = void (*)();


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
    *    Get information about plugin library
    *
    *  @return
    *    Identification string from plugin library
    */
    const char * pluginInfo();

    /**
    *  @brief
    *    Initialize plugin library
    */
    void initPlugin();

    /**
    *  @brief
    *    De-initialize plugin library
    */
    void deinitPlugin();

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
    GetPluginInfoPtr                 m_getPluginInfoPtr; ///< Pointer to function getPluginInfo()
    InitPluginPtr                    m_initPluginPtr;    ///< Pointer to function initPlugin()
    DeInitPluginPtr                  m_deinitPluginPtr;  ///< Pointer to function deinitPlugin()
    std::vector<AbstractComponent *> m_components;       ///< List of components that belong to the plugin library
};


} // namespace cppexpose
