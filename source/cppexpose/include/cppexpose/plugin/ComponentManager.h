
#pragma once


#include <string>
#include <vector>
#include <map>

#include <cppexpose/signal/Signal.h>


namespace cppexpose
{


class PluginLibrary;
class AbstractComponent;


/**
*  @brief
*    Class for loading and managing plugins
*/
class CPPEXPOSE_API ComponentManager
{
public:
    Signal<> pluginsChanged;


public:
    /**
    *  @brief
    *    Constructor
    */
    ComponentManager();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ComponentManager();

    /**
    *  @brief
    *    Get plugin search paths
    *
    *  @return
    *    List of paths that are searched for plugins
    */
    const std::vector<std::string> & searchPaths() const;

    /**
    *  @brief
    *    Set plugin search paths
    *
    *  @param[in] paths
    *    List of paths that are searched for plugins
    */
    void setSearchPaths(const std::vector<std::string> & paths);

    /**
    *  @brief
    *    Add plugin search path
    *
    *  @param[in] path
    *    Plugin search path
    *
    *  @remarks
    *    If path is empty or already in the path list, the path list is not changed.
    *    If no plugin path is provided, the default application path is used.
    */
    void addSearchPath(const std::string & path);

    /**
    *  @brief
    *    Remove plugin search path
    *
    *  @param[in] path
    *    Plugin search path
    */
    void removeSearchPath(const std::string & path);

    /**
    *  @brief
    *    Scan for plugins and load all found ones
    *
    *  @param[in] identifier
    *    Load only plugins with the given identifier as a substring
    *  @param[in] reload
    *    Reload plugin libraries that are already loaded?
    */
    void scan(const std::string & identifier = "", bool reload = false);

    /**
    *  @brief
    *    Load plugin library
    *
    *  @param[in] filePath
    *    Path to the plugin library
    *  @param[in] reload
    *    Reload plugin libraries that are already loaded?
    *
    *  @return
    *    'true' if library has been loaded successfully, else 'false'
    */
    bool load(const std::string & filePath, bool reload = true);

    /**
    *  @brief
    *    Get list of available components
    *
    *  @return
    *    List of components
    */
    const std::vector<AbstractComponent *> & components() const;

    /**
    *  @brief
    *    Add component
    *
    *  @param[in] component
    *    Component
    */
    void addComponent(AbstractComponent * component);

    /**
    *  @brief
    *    Get list of loaded plugin libraries
    *
    *  @return
    *    List of plugin libraries
    */
    const std::vector<PluginLibrary *> pluginLibraries() const;

    /**
    *  @brief
    *    Get component by name
    *
    *  @param[in] name
    *    Component name
    *
    *  @return
    *    Pointer to the component, nullptr if no component with that name exists
    */
    AbstractComponent * component(const std::string & name) const;

    /**
    *  @brief
    *    Print list of available components to log
    */
    void printComponents() const;


protected:
    /**
    *  @brief
    *    Load plugin library and add all contained plugins
    *
    *  @param[in] filePath
    *    Path to library
    *  @param[in] reload
    *    Reload plugin libraries that are already loaded?
    *
    *  @return
    *    'true' if library has been loaded successfully, else 'false'
    */
    bool loadLibrary(const std::string & filePath, bool reload);

    /**
    *  @brief
    *    Unload plugin library
    *
    *  @param[in] library
    *    Plugin library
    *
    *  @remarks
    *    Before calling the function, it must be made sure that the plugin
    *    library is not used anymore, i.e., no instances of the contained
    *    plugins must be remaining.
    */
    void unloadLibrary(PluginLibrary * library);


protected:
    std::vector<std::string>                   m_paths;               ///< Search paths for plugins
    std::vector<AbstractComponent *>           m_components;          ///< Available components
    std::map<std::string, PluginLibrary *>     m_librariesByFilePath; ///< Available components by path
    std::map<std::string, AbstractComponent *> m_componentsByName;    ///< Available components by name
};


} // namespace cppexpose
