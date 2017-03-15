
#include <cppexpose/plugin/ComponentRegistry.h>


namespace cppexpose
{


ComponentRegistry::ComponentRegistry()
{
}

ComponentRegistry::~ComponentRegistry()
{
}

const std::vector<AbstractComponent *> & ComponentRegistry::components() const
{
    return m_components;
}

void ComponentRegistry::addComponent(AbstractComponent * component)
{
    m_components.push_back(component);
}

void ComponentRegistry::clear()
{
    m_components.clear();
}


} // namespace cppexpose
