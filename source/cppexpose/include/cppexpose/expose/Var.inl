
#pragma once


namespace cppexpose
{


template <typename Type>
Var<Type>::Var()
: GetTyped< Type, ValueStorage<Type> >::VarType()
{
}

template <typename Type>
Var<Type>::Var(const Type & value)
: GetTyped< Type, ValueStorage<Type> >::VarType(value)
{
}

template <typename Type>
template <typename... Args>
Var<Type>::Var(const Type & value, Args&&... args)
: GetTyped< Type, ValueStorage<Type> >::VarType(value, std::forward<Args>(args)...)
{
}

template <typename Type>
Var<Type>::Var(const std::string & name, PropertyContainer * parent)
: GetTyped< Type, ValueStorage<Type> >::VarType()
{
    this->registerProperty(name, parent);
}

template <typename Type>
Var<Type>::Var(const std::string & name, PropertyContainer * parent, const Type & value)
: GetTyped< Type, ValueStorage<Type> >::VarType(value)
{
    this->registerProperty(name, parent);
}

template <typename Type>
template <typename... Args>
Var<Type>::Var(const std::string & name, PropertyContainer * parent, const Type & value, Args&&... args)
: GetTyped< Type, ValueStorage<Type> >::VarType(value, std::forward<Args>(args)...)
{
    this->registerProperty(name, parent);
}

template <typename Type>
Var<Type>::Var(const Var<Type> & var)
: GetTyped< Type, ValueStorage<Type> >::VarType(static_cast<const AbstractVar &>(var))
{
}

template <typename Type>
Var<Type>::Var(const AbstractVar & var)
: GetTyped< Type, ValueStorage<Type> >::VarType(static_cast<const AbstractVar &>(var))
{
}

template <typename Type>
Var<Type>::~Var()
{
}

template <typename Type>
Var<Type> & Var<Type>::operator =(const AbstractVar & var)
{
    this->fromVar(var);
    return *this;
}

template <typename Type>
std::unique_ptr<AbstractVar> Var<Type>::move()
{
    // Copy primitive values instead of moving
    return std::unique_ptr<AbstractVar>(new Var<Type>(*this));
}


} // namespace cppexpose
