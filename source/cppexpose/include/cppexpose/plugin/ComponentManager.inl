
#pragma once


#include <algorithm>


namespace cppexpose
{


template <typename BaseType>
std::vector<typename ComponentTypes<BaseType>::AbstractComponentType *> ComponentManager::components() const
{
    using AbstractComponentType = typename ComponentTypes<BaseType>::AbstractComponentType;

    // Find new components
    updateComponents();

    // Assume that on average, half the components matches Type
    std::vector<AbstractComponentType *> typedComponents;
    typedComponents.reserve(m_components.size() / 2);

    for (AbstractComponent * component : m_components)
    {
        auto typedComponent = dynamic_cast<AbstractComponentType *>(component);
        if (typedComponent != nullptr)
        {
            typedComponents.push_back(typedComponent);
        }
    }

    return typedComponents;
}

template <typename BaseType>
typename ComponentTypes<BaseType>::AbstractComponentType * ComponentManager::component(const std::string & name) const
{
    using AbstractComponentType = typename ComponentTypes<BaseType>::AbstractComponentType;

    return dynamic_cast<AbstractComponentType *>(this->component(name));
}


} // namespace cppexpose
