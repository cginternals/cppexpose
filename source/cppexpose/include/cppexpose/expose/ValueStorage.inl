
#pragma once


namespace cppexpose
{


// Non-const type
template <typename Type, typename BaseClass>
ValueStorage<Type, BaseClass>::ValueStorage()
{
}

template <typename Type, typename BaseClass>
ValueStorage<Type, BaseClass>::ValueStorage(const AbstractVar & var)
: AbstractTyped<Type, BaseClass>()
, m_value(var.value<Type>())
{
}

template <typename Type, typename BaseClass>
ValueStorage<Type, BaseClass>::ValueStorage(const Type &, const AbstractVar & var)
: AbstractTyped<Type, BaseClass>()
, m_value(var.value<Type>())
{
}

template <typename Type, typename BaseClass>
ValueStorage<Type, BaseClass>::ValueStorage(const Type &, const Type & value)
: AbstractTyped<Type, BaseClass>()
, m_value(value)
{
}

template <typename Type, typename BaseClass>
ValueStorage<Type, BaseClass>::ValueStorage(const Type & defaultValue)
: AbstractTyped<Type, BaseClass>()
, m_value(defaultValue)
{
}

template <typename Type, typename BaseClass>
ValueStorage<Type, BaseClass>::~ValueStorage()
{
}

template <typename Type, typename Storage>
AbstractVar * ValueStorage<Type, Storage>::clone() const
{
    return new Var<Type>(this->value());
}

template <typename Type, typename BaseClass>
bool ValueStorage<Type, BaseClass>::isConst() const
{
    return false;
}

template <typename Type, typename BaseClass>
const Type & ValueStorage<Type, BaseClass>::value() const
{
    return m_value;
}

template <typename Type, typename BaseClass>
void ValueStorage<Type, BaseClass>::setValue(const Type & value)
{
    m_value = value;
}


// Const type
template <typename Type, typename BaseClass>
ValueStorage<const Type, BaseClass>::ValueStorage()
{
}

template <typename Type, typename BaseClass>
ValueStorage<const Type, BaseClass>::ValueStorage(const AbstractVar & var)
: AbstractTyped<Type, BaseClass>()
, m_value(var.value<Type>())
{
}

template <typename Type, typename BaseClass>
ValueStorage<const Type, BaseClass>::ValueStorage(const Type &, const AbstractVar & var)
: AbstractTyped<Type, BaseClass>()
, m_value(var.value<Type>())
{
}

template <typename Type, typename BaseClass>
ValueStorage<const Type, BaseClass>::ValueStorage(const Type &, const Type & value)
: AbstractTyped<Type, BaseClass>()
, m_value(value)
{
}

template <typename Type, typename BaseClass>
ValueStorage<const Type, BaseClass>::ValueStorage(const Type & defaultValue)
: AbstractTyped<Type, BaseClass>()
, m_value(defaultValue)
{
}

template <typename Type, typename BaseClass>
ValueStorage<const Type, BaseClass>::~ValueStorage()
{
}

template <typename Type, typename Storage>
AbstractVar * ValueStorage<const Type, Storage>::clone() const
{
    return new Var<const Type>(this->value());
}

template <typename Type, typename BaseClass>
bool ValueStorage<const Type, BaseClass>::isConst() const
{
    return true;
}

template <typename Type, typename BaseClass>
const Type & ValueStorage<const Type, BaseClass>::value() const
{
    return m_value;
}

template <typename Type, typename BaseClass>
void ValueStorage<const Type, BaseClass>::setValue(const Type &)
{
}


} // namespace cppexpose
