
#pragma once


#include <vector>

#include <cppexpose/plugin/Component.h>


#ifdef _MSC_VER
#   define CPPEXPOSE_PLUGIN_API __declspec(dllexport)
#elif __GNUC__
#   define CPPEXPOSE_PLUGIN_API __attribute__ ((visibility ("default")))
#else
#   define CPPEXPOSE_PLUGIN_API __attribute__ ((visibility ("default")))
#endif


#define CPPEXPOSE_DECLARE_COMPONENT(TYPE, BASETYPE) \
    public: \
        static cppexpose::Component<TYPE, BASETYPE> Component;

#define CPPEXPOSE_COMPONENT(TYPE, BASETYPE, SUBTYPE, ICON, ANNOTATIONS, DESCRIPTION, VENDOR, VERSION) \
    cppexpose::Component<TYPE, BASETYPE> TYPE::Component( \
        #TYPE, \
        DESCRIPTION, \
        #BASETYPE, \
        SUBTYPE, \
        ICON, \
        ANNOTATIONS, \
        VENDOR, \
        VERSION \
    );

#define CPPEXPOSE_PLUGIN_LIBRARY \
    static std::vector<cppexpose::AbstractComponent *> g_components; \
    \
    extern "C" CPPEXPOSE_PLUGIN_API void initialize() \
    {

#define CPPEXPOSE_PLUGIN_COMPONENT(CLASS) \
        g_components.push_back(&CLASS::Component);

#define CPPEXPOSE_PLUGIN_LIBRARY_END \
    } \
    \
    extern "C" CPPEXPOSE_PLUGIN_API int numComponents() \
    { \
        return (int)g_components.size(); \
    } \
    \
    extern "C" CPPEXPOSE_PLUGIN_API cppexpose::AbstractComponent * component(unsigned int index) \
    { \
        if (index < (unsigned int)g_components.size()) \
            return g_components[index]; \
        \
        return nullptr; \
    } \
    \
    extern "C" CPPEXPOSE_PLUGIN_API void deinitialize() \
    { \
        g_components.clear(); \
    }
