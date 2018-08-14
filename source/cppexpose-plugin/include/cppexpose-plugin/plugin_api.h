
#pragma once


#include <vector>

#include <cppexpose-plugin/ComponentManager.h>
#include <cppexpose-plugin/ComponentRegistry.h>
#include <cppexpose-plugin/Component.h>


#define CPPEXPOSE_DECLARE_COMPONENT(TYPE, BASETYPE, TAGS, ICON, ANNOTATIONS, DESCRIPTION, VENDOR, VERSION) \
    class ComponentType : public cppexpose_plugin::Component<TYPE, BASETYPE> \
    { \
    public: \
        ComponentType() \
        : cppexpose_plugin::Component<TYPE, BASETYPE>( \
            #TYPE, \
            DESCRIPTION, \
            #BASETYPE, \
            TAGS, \
            ICON, \
            ANNOTATIONS, \
            VENDOR, \
            VERSION) \
        { \
            cppexpose_plugin::ComponentManager::registry().addComponent(this); \
        } \
    }; \
    \
    static ComponentType Component;

#define CPPEXPOSE_COMPONENT(TYPE, BASETYPE) \
    TYPE::ComponentType TYPE::Component;
