
#pragma once


namespace cppexpose
{


template <typename Type>
Property<Type>::Property(const Type & value)
: GetTyped< Type, ValueStorage<Type, AbstractProperty> >::VarType(value)
{
}

template <typename Type>
template <typename... Args>
Property<Type>::Property(const Type & value, Args&&... args)
: GetTyped< Type, ValueStorage<Type, AbstractProperty> >::VarType(value, std::forward<Args>(args)...)
{
}

template <typename Type>
Property<Type>::Property(const std::string & name, PropertyContainer * parent)
: GetTyped< Type, ValueStorage<Type, AbstractProperty> >::VarType()
{
    this->registerProperty(name, parent);
}

template <typename Type>
Property<Type>::Property(const std::string & name, PropertyContainer * parent, const Type & value)
: GetTyped< Type, ValueStorage<Type, AbstractProperty> >::VarType(value)
{
    this->registerProperty(name, parent);
}

template <typename Type>
template <typename... Args>
Property<Type>::Property(const std::string & name, PropertyContainer * parent, const Type & value, Args&&... args)
: GetTyped< Type, ValueStorage<Type, AbstractProperty> >::VarType(value, std::forward<Args>(args)...)
{
    this->registerProperty(name, parent);
}

template <typename Type>
Property<Type>::Property(const Property<Type> & prop)
: GetTyped< Type, ValueStorage<Type, AbstractProperty> >::VarType(static_cast<const AbstractVar &>(prop))
{
}

template <typename Type>
Property<Type>::Property(const AbstractVar & var)
: GetTyped< Type, ValueStorage<Type, AbstractProperty> >::VarType(static_cast<const AbstractVar &>(var))
{
}

template <typename Type>
Property<Type>::~Property()
{
}

template <typename Type>
Property<Type> & Property<Type>::operator =(const AbstractVar & var)
{
    this->fromVar(var);
    return *this;
}

template <typename Type>
std::unique_ptr<AbstractVar> Property<Type>::move()
{
    // Copy primitive values instead of moving
    return std::unique_ptr<AbstractVar>(new Property<Type>(*this));
}


} // namespace cppexpose
