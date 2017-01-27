
#pragma once


#include <string>
#include <vector>
#include <map>

#include <cppexpose/signal/Signal.h>
#include <cppexpose/plugin/ComponentHelpers.h>


namespace cppexpose
{


class PluginLibrary;


/**
*  @brief
*    Plugin path type (to distinguish between automatic and user-defined paths)
*/
enum class PluginPathType
{
    All             ///< All plugin paths
  , Internal    = 1 ///< Plugin path defined by the application itself (not to be saved to config)
  , UserDefined = 2 ///< Plugin path defined by the user (saved to config)
};


/**
*  @brief
*    Class for managing components and plugins
*
*    This class manages a list of components, which can be
*    instantiated dynamically. A component, which is in fact
*    a factory object, can either be defined directly inside
*    a library or application, or be loaded from a plugin library.
*
*    The component manager offers functionality to register components,
*    list components (either all or per type), and get components
*    by name. It also provides functions for search and loading plugin
*    libraries, which in turn register components on the component manager.
*/
class CPPEXPOSE_API ComponentManager
{
public:
    Signal<> componentsChanged; ///< Called when a component has been added


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
    *    Get plugin paths
    *
    *  @param[in] type
    *    Plugin path type
    *
    *  @return
    *    List of paths that are searched for plugins
    */
    const std::vector<std::string> & pluginPaths(PluginPathType type = PluginPathType::UserDefined) const;

    /**
    *  @brief
    *    Add plugin path
    *
    *  @param[in] path
    *    Plugin path
    *  @param[in] type
    *    Plugin path type
    *
    *  @remarks
    *    If path is empty or already in the path list, the path list is not changed.
    *    If no plugin path is provided, the default application path is used.
    *    The type must be either UserDefined or Internal, calls to addPluginPath
    *    with PluginPathType::All are ignored.
    */
    void addPluginPath(const std::string & path, PluginPathType type = PluginPathType::UserDefined);

    /**
    *  @brief
    *    Remove plugin path
    *
    *  @param[in] path
    *    Plugin path
    */
    void removePluginPath(const std::string & path);

    /**
    *  @brief
    *    Scan for plugins and load all found ones
    *
    *  @param[in] identifier
    *    Load only plugins with the given identifier as a substring
    *  @param[in] reload
    *    Reload plugin libraries that are already loaded?
    */
    void scanPlugins(const std::string & identifier = "", bool reload = false);

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
    bool loadPlugin(const std::string & filePath, bool reload = true);

    /**
    *  @brief
    *    Get list of loaded plugin libraries
    *
    *  @return
    *    List of plugin libraries
    */
    std::vector<PluginLibrary *> pluginLibraries() const;

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
    *    Get list of available components of a specific type
    *
    *  @return
    *    List of typed components
    */
    template <typename BaseType>
    std::vector<typename ComponentTypes<BaseType>::AbstractComponentType *> components() const;

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
    *    Get typed component
    *
    *  @param[in] name
    *    Component name
    *
    *  @return
    *    Pointer to the component, nullptr if component doesn't exist or has the wrong type
    */
    template <typename BaseType>
    typename ComponentTypes<BaseType>::AbstractComponentType * component(const std::string & name) const;

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
    std::vector<std::string>                   m_paths;               ///< Plugin paths (all)
    std::vector<std::string>                   m_pathsInternal;       ///< Plugin paths (internal)
    std::vector<std::string>                   m_pathsUser;           ///< Plugin paths (user defined)
    std::vector<AbstractComponent *>           m_components;          ///< Available components
    std::map<std::string, PluginLibrary *>     m_librariesByFilePath; ///< Available components by path
    std::map<std::string, AbstractComponent *> m_componentsByName;    ///< Available components by name
};


} // namespace cppexpose


#include <cppexpose/plugin/ComponentManager.inl>
