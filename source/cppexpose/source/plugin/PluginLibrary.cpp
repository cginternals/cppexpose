
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
    const int RTLD_LAZY = 0; // Ignore lazy-flag for win32 - see dlopen

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
, m_handle(0)
{
    // Open library
    m_handle = dlopen(filePath.c_str(), RTLD_LAZY);
    if (!m_handle)
    {
        // Could not be opened
        cppassist::warning() << dlerror();
        return;
    }
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
    return (m_handle != 0);
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
