
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

#include <cppexpose/plugin/PluginLibrary.h>
#include <cppexpose/plugin/AbstractComponent.h>


namespace cppexpose
{


ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
    // Note: The plugins do not need to (and must not) be destroyed, because this is done
    // inside the plugin library, when deinitialize() is called.

    // Unload plugin libraries
    for (const auto & it : m_librariesByFilePath) {
        unloadLibrary(it.second.get());
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
    // Return list of plugins
    return m_components;
}

AbstractComponent * ComponentManager::component(const std::string & name) const
{
    // Check if plugin exists
    const auto it = m_componentsByName.find(name);

    if (it == m_componentsByName.end())
    {
        return nullptr;
    }

    // Return plugin
    return it->second;
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
    if (!library->isValid())
    {
        // Loading failed. Destroy library object and return failure.
        cppassist::warning() << (alreadyLoaded ? "Reloading" : "Loading") << " plugin(s) from '" << filePath << "' failed.";

        return false;
    }

    // If library was already loaded, unload previous incarnation.
    if (alreadyLoaded) {
        unloadLibrary(it->second.get());
    }

    // Initialize plugin library
    library->initialize();

    // Iterate over plugins
    size_t numComponents = library->numComponents();
    for (auto i = size_t(0); i < numComponents; ++i)
    {
        // Get component
        AbstractComponent * component = library->component(i);
        if (!component)
            continue;

        // Set module information
        if (!modInfo.empty())
        {
            component->setModuleInfo(modInfo);
        }

        // Add component to list
        m_components.push_back(component);

        // Save component by name
        m_componentsByName[component->name()] = component;
    }

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

    // Unload plugin library
    library->deinitialize();
    m_librariesByFilePath.erase(it);
}


} // namespace cppexpose
