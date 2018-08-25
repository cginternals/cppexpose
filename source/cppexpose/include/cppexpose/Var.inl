
#pragma once


namespace cppexpose
{


template <typename Type>
Var<Type>::Var()
: GetTyped<Type>::VarType()
{
}

template <typename Type>
Var<Type>::Var(const Type & value)
: GetTyped<Type>::VarType(value)
{
}

template <typename Type>
template <typename... Args>
Var<Type>::Var(const Type & value, Args&&... args)
: GetTyped<Type>::VarType(value, std::forward<Args>(args)...)
{
}

template <typename Type>
Var<Type>::Var(PropertyContainer * parent, const std::string & name)
: GetTyped<Type>::VarType()
{
    this->registerProperty(parent, name);
}

template <typename Type>
Var<Type>::Var(PropertyContainer * parent, const std::string & name, const Type & value)
: GetTyped<Type>::VarType(value)
{
    this->registerProperty(parent, name);
}

template <typename Type>
template <typename... Args>
Var<Type>::Var(PropertyContainer * parent, const std::string & name, const Type & value, Args&&... args)
: GetTyped<Type>::VarType(value, std::forward<Args>(args)...)
{
    this->registerProperty(parent, name);
}

template <typename Type>
Var<Type>::Var(const AbstractVar & var)
: GetTyped<Type>::VarType(var)
{
}

template <typename Type>
Var<Type>::~Var()
{
}

template <typename Type>
Var<Type> & Var<Type>::operator =(const Var<Type> & var)
{
    this->setValue(var.value());
    return *this;
}

template <typename Type>
Var<Type> & Var<Type>::operator =(const AbstractVar & var)
{
    this->fromVar(var);
    return *this;
}

template <typename Type>
Var<Type> & Var<Type>::operator =(const Type & value)
{
    this->setValue(value);
    return *this;
}

template <typename Type>
std::unique_ptr<AbstractVar> Var<Type>::move()
{
    // Copy primitive values instead of moving
    return std::unique_ptr<AbstractVar>(new Var<Type>(*this));
}


} // namespace cppexpose
