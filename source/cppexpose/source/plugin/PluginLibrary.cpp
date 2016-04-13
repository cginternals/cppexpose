
#include <cppexpose/plugin/PluginLibrary.h>

#ifdef WIN32
    #include <Windows.h>
#else
    #include <dlfcn.h>
    #include <libgen.h>
    #include <dirent.h>
#endif

#include <loggingzeug/logging.h>

#include <cppexpose/plugin/AbstractComponent.h>


#ifdef WIN32

namespace
{
    const int RTLD_LAZY(0); // Ignore lazy-flag for win32 - see dlopen

    inline HMODULE dlopen(LPCSTR lpFileName, int ignore)
    {
        return LoadLibraryA(lpFileName);
    }

    inline FARPROC dlsym(HMODULE hModule, LPCSTR lpProcName)
    {
        return GetProcAddress(hModule, lpProcName);
    }

    inline BOOL dlclose(HMODULE hModule)
    {
        return FreeLibrary(hModule);
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
, m_handle(0)
, m_initPtr(nullptr)
, m_deinitPtr(nullptr)
, m_numComponentsPtr(nullptr)
, m_componentPtr(nullptr)
{
    // Open library
    m_handle = dlopen(filePath.c_str(), RTLD_LAZY);
    if (!m_handle)
    {
        // Could not be opened
        loggingzeug::warning() << dlerror();
        return;
    }

    // Get pointers to exported functions
    *reinterpret_cast<void**>(&m_initPtr)          = dlsym(m_handle, "initialize");
    *reinterpret_cast<void**>(&m_deinitPtr)        = dlsym(m_handle, "deinitialize");
    *reinterpret_cast<void**>(&m_numComponentsPtr) = dlsym(m_handle, "numComponents");
    *reinterpret_cast<void**>(&m_componentPtr)     = dlsym(m_handle, "component");
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
    return (m_initPtr && m_numComponentsPtr && m_componentPtr && m_deinitPtr);
}

void PluginLibrary::initialize()
{
    if (m_initPtr != nullptr)
    {
        (*m_initPtr)();
    }
}

void PluginLibrary::deinitialize()
{
    if (m_deinitPtr != nullptr)
    {
        (*m_deinitPtr)();
    }
}

unsigned int PluginLibrary::numComponents() const
{
    if (m_numComponentsPtr != nullptr)
    {
        return (*m_numComponentsPtr)();
    }

    return 0;
}

cppexpose::AbstractComponent * PluginLibrary::component(unsigned int index) const
{
    if (m_componentPtr != nullptr)
    {
        return (*m_componentPtr)(index);
    }

    return nullptr;
}


} // namespace cppexpose
