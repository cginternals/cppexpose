
#pragma once


#include <cppexpose/plugin/ComponentManager.h>


namespace cppexpose
{


template <typename Type>
const std::vector<TypedComponent<Type> *> ComponentManager::components() const
{
    std::vector<TypedComponent<Type> *> typedComponents;

    const std::vector<AbstractComponent *> & all = this->components();
    for (AbstractComponent * component : all)
    {
        TypedComponent<Type> * typed = dynamic_cast<TypedComponent<Type> *>(component);
        if (typed != nullptr) {
            typedComponents.push_back(typed);
        }
    }

    return typedComponents;
}

template <typename Type>
TypedComponent<Type> * ComponentManager::component(const std::string & name) const
{
    // Get component
    AbstractComponent * component = this->component(name);
    if (!component) {
        return nullptr;
    }

    // Cast to typed component
    TypedComponent<Type> * typed = dynamic_cast<TypedComponent<Type> *>(component);
    return typed;
}


} // namespace cppexpose
