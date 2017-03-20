
#pragma once


#include <vector>

#include <cppexpose/plugin/ComponentManager.h>
#include <cppexpose/plugin/ComponentRegistry.h>
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
            cppexpose::ComponentManager::registry().addComponent(this); \
        } \
    }; \
    \
    static ComponentType Component;

#define CPPEXPOSE_COMPONENT(TYPE, BASETYPE) \
    TYPE::ComponentType TYPE::Component;

#define CPPEXPOSE_PLUGIN_LIBRARY \
    extern "C" CPPEXPOSE_PLUGIN_API const char * getPluginInfo() \
    { \
        return "cppexpose_plugin"; \
    }

#define CPPEXPOSE_PLUGIN_LIBRARY_INIT \
    extern "C" CPPEXPOSE_PLUGIN_API void initPlugin()

#define CPPEXPOSE_PLUGIN_LIBRARY_DEINIT \
    extern "C" CPPEXPOSE_PLUGIN_API void deinitPlugin()

// Not needed any more, left for compatibility reasons
#define CPPEXPOSE_PLUGIN_COMPONENT(CLASS)

#define CPPEXPOSE_PLUGIN_LIBRARY_END
