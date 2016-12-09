
#pragma once


#include <algorithm>


namespace cppexpose
{


template <typename Type>
std::vector<TypedComponent<Type> *> ComponentManager::components() const
{
    std::vector<TypedComponent<Type> *> typedComponents;

    const std::vector<AbstractComponent *> & all = this->components();

    // assume that on average, half the components matches Type
    typedComponents.reserve(all.size() / 2);

    for (AbstractComponent * component : all)
    {
        auto typedComponent = dynamic_cast<TypedComponent<Type> *>(component);
        if (typedComponent != nullptr)
        {
            typedComponents.push_back(typedComponent);
        }
    }

    return typedComponents;
}

template <typename Type>
TypedComponent<Type> * ComponentManager::component(const std::string & name) const
{
    return dynamic_cast<TypedComponent<Type> *>(this->component(name));
}


} // namespace cppexpose
