
#pragma once


namespace cppexpose
{


// Read/write type
template <typename T, typename BASE>
StoredValueArray<T, BASE>::StoredValueArray(
    std::function<T ()> getter
  , std::function<void(const T &)> setter
  , std::function<ElementType (int)> elementGetter
  , std::function<void(int, const ElementType &)> elementSetter)
: m_getter(getter)
, m_setter(setter)
, m_elementGetter(elementGetter)
, m_elementSetter(elementSetter)
{
}

template <typename T, typename BASE>
template <typename Obj>
StoredValueArray<T, BASE>::StoredValueArray(
    Obj * obj,
    typename ArrayValueFunctions<T, ElementType, Obj>::getter g,
    typename ArrayValueFunctions<T, ElementType, Obj>::setter s,
    typename ArrayValueFunctions<T, ElementType, Obj>::elementGetter eg,
    typename ArrayValueFunctions<T, ElementType, Obj>::elementSetter es)
{
    typename ArrayValueFunctions<T, ElementType, Obj>::getter getter = g;
    typename ArrayValueFunctions<T, ElementType, Obj>::setter setter = s;
    typename ArrayValueFunctions<T, ElementType, Obj>::elementGetter elementGetter = eg;
    typename ArrayValueFunctions<T, ElementType, Obj>::elementSetter elementSetter = es;

    m_getter = [obj, getter] () -> T
    {
        return (obj->*getter)();
    };

    m_setter = [obj, setter] (const T & value)
    {
        (obj->*setter)(value);
    };

    m_elementGetter = [obj, elementGetter] (int index) -> ElementType
    {
        return (obj->*elementGetter)(index);
    };

    m_elementSetter = [obj, elementSetter] (int index, const ElementType & value)
    {
        (obj->*elementSetter)(index, value);
    };
}

template <typename T, typename BASE>
StoredValueArray<T, BASE>::~StoredValueArray()
{
}

template <typename T, typename BASE>
std::unique_ptr<AbstractTyped> StoredValueArray<T, BASE>::clone() const
{
    return cppassist::make_unique<StoredValueArray<T, AbstractTyped>>(m_getter, m_setter, m_elementGetter, m_elementSetter);
}

template <typename T, typename BASE>
T StoredValueArray<T, BASE>::value() const
{
    return m_getter();
}

template <typename T, typename BASE>
void StoredValueArray<T, BASE>::setValue(const T & value)
{
    m_setter(value);
    this->onValueChanged(value);
}

template <typename T, typename BASE>
const T * StoredValueArray<T, BASE>::ptr() const
{
    return nullptr;
}

template <typename T, typename BASE>
T * StoredValueArray<T, BASE>::ptr()
{
    return nullptr;
}

template <typename T, typename BASE>
typename StoredValueArray<T, BASE>::ElementType StoredValueArray<T, BASE>::getElement(size_t i) const
{
    return m_elementGetter(i);
}

template <typename T, typename BASE>
void StoredValueArray<T, BASE>::setElement(size_t i, const typename StoredValueArray<T, BASE>::ElementType & value)
{
    m_elementSetter(i, value);
    this->onValueChanged(this->value());
}

template <typename T, typename BASE>
StoredValueArray<T, BASE>::StoredValueArray()
{
}

template <typename T, typename BASE>
StoredValueArray<T, BASE>::StoredValueArray(
    std::function<T ()> getter
  , std::function<ElementType (int)> elementGetter)
: m_getter(getter)
, m_elementGetter(elementGetter)
{
}


// Read-only type
template <typename T, typename BASE>
StoredValueArray<const T, BASE>::StoredValueArray(
    std::function<T ()> getter
  , std::function<typename StoredValueArray<T, BASE>::ElementType (int)> elementGetter)
: StoredValueArray<T, BASE>::StoredValueArray(getter, elementGetter)
{
}

template <typename T, typename BASE>
template <typename Obj>
StoredValueArray<const T, BASE>::StoredValueArray(
    Obj * obj,
    typename ArrayValueFunctions<T, typename StoredValueArray<T, BASE>::ElementType, Obj>::getter g,
    typename ArrayValueFunctions<T, typename StoredValueArray<T, BASE>::ElementType, Obj>::elementGetter eg)
{
    typename ArrayValueFunctions<T, typename StoredValueArray<T, BASE>::ElementType, Obj>::getter getter = g;
    typename ArrayValueFunctions<T, typename StoredValueArray<T, BASE>::ElementType, Obj>::elementGetter elementGetter = eg;

    this->m_getter = [obj, getter] () -> T
    {
        return (obj->*getter)();
    };

    this->m_elementGetter = [obj, elementGetter] (int index) -> typename StoredValueArray<T, BASE>::ElementType
    {
        return (obj->*elementGetter)(index);
    };
}

template <typename T, typename BASE>
StoredValueArray<const T, BASE>::~StoredValueArray()
{
}

template <typename T, typename BASE>
std::unique_ptr<AbstractTyped> StoredValueArray<const T, BASE>::clone() const
{
    return cppassist::make_unique<StoredValueArray<const T, AbstractTyped>>(
      this->m_getter,
      this->m_setter,
      this->m_elementGetter,
      this->m_elementSetter
    );
}

template <typename T, typename BASE>
bool StoredValueArray<const T, BASE>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T, typename BASE>
void StoredValueArray<const T, BASE>::setValue(const T &)
{
    // Read-only!
}

template <typename T, typename BASE>
void StoredValueArray<const T, BASE>::setElement(size_t, const typename StoredValueArray<T, BASE>::ElementType &)
{
    // Read-only!
}


} // namespace cppexpose
