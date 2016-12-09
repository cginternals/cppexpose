
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

    std::copy_if(all.begin(), all.end(), std::back_inserter(typedComponents), [](AbstractComponent * component) {
        return dynamic_cast<TypedComponent<Type> *>(component) != nullptr;
    });

    return typedComponents;
}

template <typename Type>
TypedComponent<Type> * ComponentManager::component(const std::string & name) const
{
    return dynamic_cast<TypedComponent<Type> *>(this->component(name));
}


} // namespace cppexpose
