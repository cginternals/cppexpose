
#pragma once


namespace cppexpose
{


// Read/write type
template <typename T, typename BASE>
StoredValueSingle<T, BASE>::StoredValueSingle(
    std::function<T ()> getter
  , std::function<void(const T &)> setter)
: m_getter(getter)
, m_setter(setter)
{
}

template <typename T, typename BASE>
template <typename Obj>
StoredValueSingle<T, BASE>::StoredValueSingle(
    Obj * o,
    typename SingleValueFunctions<T, Obj>::getter g,
    typename SingleValueFunctions<T, Obj>::setter s)
{
    Obj * obj = o;
    typename SingleValueFunctions<T, Obj>::getter getter = g;
    typename SingleValueFunctions<T, Obj>::setter setter = s;

    m_getter = [obj, getter] () -> T
    {
        return (obj->*getter)();
    };

    m_setter = [obj, setter] (const T & value)
    {
        (obj->*setter)(value);
    };
}

template <typename T, typename BASE>
StoredValueSingle<T, BASE>::~StoredValueSingle()
{
}

template <typename T, typename BASE>
AbstractTyped * StoredValueSingle<T, BASE>::clone() const
{
    return new StoredValueSingle<T, AbstractTyped>(m_getter, m_setter);
}

template <typename T, typename BASE>
T StoredValueSingle<T, BASE>::value() const
{
    return m_getter();
}

template <typename T, typename BASE>
void StoredValueSingle<T, BASE>::setValue(const T & value)
{
    m_setter(value);
    this->onValueChanged(value);
}

template <typename T, typename BASE>
const T * StoredValueSingle<T, BASE>::ptr() const
{
    return nullptr;
}

template <typename T, typename BASE>
T * StoredValueSingle<T, BASE>::ptr()
{
    return nullptr;
}

template <typename T, typename BASE>
StoredValueSingle<T, BASE>::StoredValueSingle()
{
}

template <typename T, typename BASE>
StoredValueSingle<T, BASE>::StoredValueSingle(const std::function<T ()> & getter)
: m_getter(getter)
{
}


// Read-only type
template <typename T, typename BASE>
StoredValueSingle<const T, BASE>::StoredValueSingle(std::function<T ()> getter)
: StoredValueSingle<T, BASE>::StoredValueSingle(getter)
{
}

template <typename T, typename BASE>
template <typename Obj>
StoredValueSingle<const T, BASE>::StoredValueSingle(
    Obj * o,
    typename SingleValueFunctions<T, Obj>::getter g)
{
    Obj * obj = o;
    typename SingleValueFunctions<T, Obj>::getter getter = g;

    this->m_getter = [obj, getter] () -> T
    {
        return (obj->*getter)();
    };
}

template <typename T, typename BASE>
StoredValueSingle<const T, BASE>::~StoredValueSingle()
{
}

template <typename T, typename BASE>
AbstractTyped * StoredValueSingle<const T, BASE>::clone() const
{
    return new StoredValueSingle<const T, AbstractTyped>(this->m_getter);
}

template <typename T, typename BASE>
bool StoredValueSingle<const T, BASE>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T, typename BASE>
void StoredValueSingle<const T, BASE>::setValue(const T &)
{
    // Read-only!
}


} // namespace cppexpose
