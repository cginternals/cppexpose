
#pragma once


namespace cppexpose
{


template <typename Type>
Var<Type>::Var()
: GetTyped< Type, ValueStorage<Type, AbstractVar> >::VarType()
{
}

template <typename Type>
Var<Type>::Var(const Var<Type> & var)
: GetTyped< Type, ValueStorage<Type, AbstractVar> >::VarType(static_cast<const AbstractVar &>(var))
{
}

template <typename Type>
Var<Type>::Var(const AbstractVar & var)
: GetTyped< Type, ValueStorage<Type, AbstractVar> >::VarType(static_cast<const AbstractVar &>(var))
{
}

template <typename Type>
template <typename... Args>
Var<Type>::Var(const Type & defaultValue, Args&&... args)
: GetTyped< Type, ValueStorage<Type, AbstractVar> >::VarType(defaultValue, std::forward<Args>(args)...)
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
