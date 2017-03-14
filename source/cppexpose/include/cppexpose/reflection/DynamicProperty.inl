
#pragma once


namespace cppexpose
{


template <typename T, typename BASE>
template <typename... Args>
DynamicProperty<T, BASE>::DynamicProperty(const std::string & name, Object * parent, Args&&... args)
: DirectValue<T, BASE>(std::forward<Args>(args)...)
{
    this->initProperty(name, parent);
}

template <typename T, typename BASE>
DynamicProperty<T, BASE>::~DynamicProperty()
{
}

template <typename T, typename BASE>
bool DynamicProperty<T, BASE>::isObject() const
{
    return false;
}

template <typename T, typename BASE>
void DynamicProperty<T, BASE>::onValueChanged(const T & value)
{
    this->valueChanged(value);
}


} // namespace cppexpose
