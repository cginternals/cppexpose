
#pragma once


#include <vector>

#include <cppexpose-plugin/cppexpose-plugin_api.h>


namespace cppexpose_plugin
{


class AbstractComponent;


/**
*  @brief
*    Registry for newly registered components
*
*    The ComponentRegister is used to register new components.
*    It as accessed via ComponentManager, where a single static
*    instance of this class is created. Components register
*    themselves at that registry when they are statically
*    initialized. When the ComponentManager update its list of
*    components, it also clears the component registry afterwards.
*/
class CPPEXPOSE_PLUGIN_API ComponentRegistry
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ComponentRegistry();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ComponentRegistry();

    /**
    *  @brief
    *    Get components
    *
    *  @return
    *    List of registered components
    */
    const std::vector<AbstractComponent *> & components() const;

    /**
    *  @brief
    *    Add component
    *
    *  @param[in] component
    *    Component (must NOT be null)
    */
    void addComponent(AbstractComponent * component);

    /**
    *  @brief
    *    Clear list of components
    */
    void clear();


protected:
    std::vector<AbstractComponent *> m_components; ///< List of registered components
};


} // namespace cppexpose_plugin
