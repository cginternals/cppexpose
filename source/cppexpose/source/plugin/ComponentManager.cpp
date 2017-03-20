
#include <cppexpose/plugin/ComponentManager.h>

#include <algorithm>
#include <sys/stat.h>

#ifdef WIN32
    #include <Windows.h>
#else
    #include <dlfcn.h>
    #include <libgen.h>
    #include <dirent.h>
#endif

#include <cpplocate/ModuleInfo.h>

#include <cppassist/fs/SystemInfo.h>
#include <cppassist/fs/FilePath.h>
#include <cppassist/fs/directorytraversal.h>

#include <cppassist/logging/logging.h>

#include <cppexpose/plugin/ComponentRegistry.h>
#include <cppexpose/plugin/PluginLibrary.h>
#include <cppexpose/plugin/AbstractComponent.h>


namespace cppexpose
{


ComponentRegistry & ComponentManager::registry()
{
    static ComponentRegistry registry;

    return registry;
}

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
    // Note: The plugins do not need to (and must not) be destroyed, because this is done
    // inside the plugin library, when deinitialize() is called.

    // Unload plugin libraries
    // Do not use iterators here, as unloadLibrary modifies m_librariesByFilePath!
    while (!m_librariesByFilePath.empty()) {
        unloadLibrary(m_librariesByFilePath.begin()->second.get());
    }
}

const std::vector<std::string> & ComponentManager::pluginPaths(PluginPathType type) const
{
    if (type == PluginPathType::Internal) {
        return m_pathsInternal;
    } else  if (type == PluginPathType::UserDefined) {
        return m_pathsUser;
    } else {
        return m_paths;
    }
}

void ComponentManager::addPluginPath(const std::string & path, PluginPathType type)
{
    // Check path and type
    if (path.empty() || type == PluginPathType::All) {
        return;
    }

    // Remove slash
    const std::string p = cppassist::FilePath(path).path();

    // Check if plugin path is already in the list
    const std::vector<std::string>::const_iterator it = std::find(m_paths.cbegin(), m_paths.cend(), p);
    if (it != m_paths.end()) {
        return;
    }

    // Add plugin path
    m_paths.push_back(p);

    if (type == PluginPathType::Internal) {
        m_pathsInternal.push_back(p);
    }

    if (type == PluginPathType::UserDefined) {
        m_pathsUser.push_back(p);
    }
}

void ComponentManager::removePluginPath(const std::string & path)
{
    // Remove slash
    const std::string p = cppassist::FilePath(path).path();

    // Remove path from list
    {
        const auto it = std::find(m_paths.begin(), m_paths.end(), p);
        if (it != m_paths.end()) m_paths.erase(it);
    }

    // Remove path from internal list
    {
        const auto it = std::find(m_pathsInternal.begin(), m_pathsInternal.end(), p);
        if (it != m_pathsInternal.end()) m_pathsInternal.erase(it);
    }

    // Remove path from user-defined list
    {
        const auto it = std::find(m_pathsUser.begin(), m_pathsUser.end(), p);
        if (it != m_pathsUser.end()) m_pathsUser.erase(it);
    }
}

void ComponentManager::scanPlugins(const std::string & identifier, bool reload)
{
    // List files in all plugin paths
    const std::vector<std::string> files = cppassist::fs::getFiles(m_paths, false);
    for (const std::string & file : files)
    {
        // Check if file is a library
        if (cppassist::FilePath(file).extension() != cppassist::SystemInfo::libExtension())
            continue;

        // Check if library name corresponds to search criteria
        if (identifier.empty() || file.find(identifier) != std::string::npos)
            loadLibrary(file, reload);
    }
}

bool ComponentManager::loadPlugin(const std::string & filePath, const bool reload)
{
    // Load plugin library
    bool res = loadLibrary(filePath, reload);

    return res;
}

std::vector<PluginLibrary *> ComponentManager::pluginLibraries() const
{
    std::vector<PluginLibrary *> pluginLibraries;
    pluginLibraries.reserve(m_librariesByFilePath.size());

    for (const auto & libraryIterator : m_librariesByFilePath)
        pluginLibraries.push_back(libraryIterator.second.get());

    return pluginLibraries;
}

const std::vector<AbstractComponent *> & ComponentManager::components() const
{
    // Find new components
    updateComponents();

    // Return list of plugins
    return m_components;
}

AbstractComponent * ComponentManager::component(const std::string & name) const
{
    // Find new components
    updateComponents();

    // Check if plugin exists
    const auto it = m_componentsByName.find(name);

    if (it == m_componentsByName.end())
    {
        return nullptr;
    }

    // Return plugin
    return it->second;
}

void ComponentManager::printComponents() const
{
    // Print info about each plugin
    for (const AbstractComponent * component : m_components)
    {
        cppassist::info() << " PLUGIN name: " << component->name() << " (" << component->type() << ")";
        cppassist::info() << " description: " << component->description();
        cppassist::info() << "     version: " << component->version();
        cppassist::info() << "      vendor: " << component->vendor();
        cppassist::info();
    }
}

bool ComponentManager::loadLibrary(const std::string & filePath, bool reload)
{
    // Check if library is already loaded and reload is not requested
    const auto it = m_librariesByFilePath.find(filePath);
    const auto alreadyLoaded = (it != m_librariesByFilePath.end());
    if (alreadyLoaded && !reload) {
        return true;
    }

    // Load module information file, if present
    cpplocate::ModuleInfo modInfo;
    modInfo.load(filePath + ".modinfo");

    // Open plugin library
    auto library = cppassist::make_unique<PluginLibrary>(filePath);

    // Check if it is a valid cppexpose plugin
    bool valid = false;
    if (library->isValid())
    {
        // Check plugin type
        std::string pluginInfo = library->pluginInfo();
        if (pluginInfo == "cppexpose_plugin") {
            valid = true;
        }
    }

    // If loading failed, destroy library object and return failure
    if (!valid)
    {
        cppassist::warning() << (alreadyLoaded ? "Reloading" : "Loading") << " plugin(s) from '" << filePath << "' failed.";

        return false;
    }

    // If library was already loaded, unload previous incarnation.
    if (alreadyLoaded) {
        unloadLibrary(it->second.get());
    }

    // Initialize plugin
    library->initPlugin();

    // Add new components from library
    updateComponents(library.get(), modInfo);

    // Add library to list (in case of reload, this overwrites the previous)
    m_librariesByFilePath[filePath] = std::move(library);

    // Return success
    return true;
}

void ComponentManager::unloadLibrary(PluginLibrary * library)
{
    // Check if library is loaded
    auto it = std::find_if(m_librariesByFilePath.begin(), m_librariesByFilePath.end(),
        [library](const std::pair<const std::string, std::unique_ptr<PluginLibrary>> & item)
        {
            return item.second.get() == library;
        });
    if (it == m_librariesByFilePath.end())
    {
        return;
    }

    // De-initialize plugin
    library->deinitPlugin();

    // Remove components belonging to the plugin library
    for (auto * component : library->components())
    {
        auto it = std::find(m_components.begin(), m_components.end(), component);
        if (it != m_components.end()) {
            m_components.erase(it);
        }

        auto it2 = m_componentsByName.find(component->name());
        if (it2 != m_componentsByName.end()) {
            m_componentsByName.erase (it2);
        }
    }

    // Unload plugin library
    m_librariesByFilePath.erase(it);
}

void ComponentManager::addComponent(AbstractComponent * component)
{
    // Add component to list
    m_components.push_back(component);

    // Save component by name
    m_componentsByName[component->name()] = component;

    // Emit signal
    componentsChanged();
}

void ComponentManager::updateComponents(PluginLibrary * library, const cpplocate::ModuleInfo & modInfo) const
{
    // Iterate over new components
    auto & registry = ComponentManager::registry();
    for (auto * component : registry.components())
    {
        // Add component to library
        if (library) {
            library->addComponent(component);
        }

        // Set module information
        if (!modInfo.empty())
        {
            component->setModuleInfo(modInfo);
        }

        // Add component to list
        const_cast<ComponentManager *>(this)->addComponent(component);
    }

    // Reset new components
    registry.clear();
}


} // namespace cppexpose
