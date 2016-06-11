
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


#define CPPEXPOSE_DECLARE_COMPONENT(TYPE, BASETYPE, TAGS, ICON, ANNOTATIONS, DESCRIPTION, VENDOR, VERSION) \
    class ComponentType : public cppexpose::Component<TYPE, BASETYPE> \
    { \
    public: \
        ComponentType() \
        : cppexpose::Component<TYPE, BASETYPE>( \
            #TYPE, \
            DESCRIPTION, \
            #BASETYPE, \
            TAGS, \
            ICON, \
            ANNOTATIONS, \
            VENDOR, \
            VERSION) \
        { \
        } \
    }; \
    \
    static ComponentType Component;

#define CPPEXPOSE_COMPONENT(TYPE, BASETYPE) \
    TYPE::ComponentType TYPE::Component;

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
