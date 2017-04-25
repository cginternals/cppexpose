
#include <cppexpose/plugin/PluginLibrary.h>

#ifdef WIN32
    #include <Windows.h>
#else
    #include <dlfcn.h>
    #include <libgen.h>
    #include <dirent.h>
#endif

#include <cppassist/logging/logging.h>

#include <cppexpose/plugin/AbstractComponent.h>


#ifdef WIN32

namespace
{
    const int RTLD_LAZY   = 0x00001; // Ignored lazy-flag for win32   - see dlopen
    const int RTLD_GLOBAL = 0x00100; // Ignored global-flag for win32 - see dlopen

    inline void * dlopen(LPCSTR lpFileName, int)
    {
        return static_cast<void *>(LoadLibraryA(lpFileName));
    }

    inline FARPROC dlsym(void * hModule, LPCSTR lpProcName)
    {
        return GetProcAddress((HMODULE)hModule, lpProcName);
    }

    inline BOOL dlclose(void * hModule)
    {
        return FreeLibrary((HMODULE)hModule);
    }

    inline DWORD dlerror()
    {
        return GetLastError();
    }
}

#endif


namespace cppexpose
{


PluginLibrary::PluginLibrary(const std::string & filePath)
: m_filePath(filePath)
, m_handle(nullptr)
, m_getPluginInfoPtr(nullptr)
, m_initPluginPtr(nullptr)
, m_deinitPluginPtr(nullptr)
{
    // Open library
    m_handle = dlopen(filePath.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (!m_handle)
    {
        // Could not be opened
        cppassist::warning() << dlerror();
        return;
    }

    // Get pointers to exported functions
    *reinterpret_cast<void**>(&m_getPluginInfoPtr) = dlsym(m_handle, "getPluginInfo");
    *reinterpret_cast<void**>(&m_initPluginPtr)    = dlsym(m_handle, "initPlugin");
    *reinterpret_cast<void**>(&m_deinitPluginPtr)  = dlsym(m_handle, "deinitPlugin");
}

PluginLibrary::~PluginLibrary()
{
    // Close library
    if (m_handle) {
        dlclose(m_handle);
    }
}

const std::string & PluginLibrary::filePath() const
{
    return m_filePath;
}

bool PluginLibrary::isValid() const
{
    return (m_getPluginInfoPtr != nullptr);
}

const char * PluginLibrary::pluginInfo()
{
    return (*m_getPluginInfoPtr)();
}

void PluginLibrary::initPlugin()
{
    if (m_initPluginPtr)
    {
        (*m_initPluginPtr)();
    }
}

void PluginLibrary::deinitPlugin()
{
    if (m_deinitPluginPtr)
    {
        (*m_deinitPluginPtr)();
    }
}

const std::vector<AbstractComponent *> & PluginLibrary::components() const
{
    return m_components;
}

void PluginLibrary::addComponent(AbstractComponent * component)
{
    m_components.push_back(component);
}


} // namespace cppexpose
