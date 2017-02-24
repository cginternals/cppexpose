
#pragma once


namespace cppexpose
{


// Read/write type
template <typename T, typename BASE>
DirectValueArray<T, BASE>::DirectValueArray()
{
}

template <typename T, typename BASE>
DirectValueArray<T, BASE>::DirectValueArray(const T & value)
: m_value(value)
{
}

template <typename T, typename BASE>
DirectValueArray<T, BASE>::~DirectValueArray()
{
}

template <typename T, typename BASE>
std::unique_ptr<AbstractTyped> DirectValueArray<T, BASE>::clone() const
{
    return cppassist::make_unique<DirectValueArray<T, AbstractTyped>>(m_value);
}

template <typename T, typename BASE>
T DirectValueArray<T, BASE>::value() const
{
    return m_value;
}

template <typename T, typename BASE>
void DirectValueArray<T, BASE>::setValue(const T & value)
{
    m_value = value;
    this->onValueChanged(m_value);
}

template <typename T, typename BASE>
const T * DirectValueArray<T, BASE>::ptr() const
{
    return &m_value;
}

template <typename T, typename BASE>
T * DirectValueArray<T, BASE>::ptr()
{
    return &m_value;
}

template <typename T, typename BASE>
typename DirectValueArray<T, BASE>::ElementType DirectValueArray<T, BASE>::getElement(size_t i) const
{
    return m_value[i];
}

template <typename T, typename BASE>
void DirectValueArray<T, BASE>::setElement(size_t i, const typename DirectValueArray<T, BASE>::ElementType & value)
{
    m_value[i] = value;
    this->onValueChanged(m_value);
}


// Read-only type
template <typename T, typename BASE>
DirectValueArray<const T, BASE>::DirectValueArray()
{
}

template <typename T, typename BASE>
DirectValueArray<const T, BASE>::DirectValueArray(const T & value)
: DirectValueArray<T, BASE>::DirectValueArray(value)
{
}

template <typename T, typename BASE>
DirectValueArray<const T, BASE>::~DirectValueArray()
{
}

template <typename T, typename BASE>
std::unique_ptr<AbstractTyped> DirectValueArray<const T, BASE>::clone() const
{
    return cppassist::make_unique<DirectValueArray<const T, AbstractTyped>>(this->m_value);
}

template <typename T, typename BASE>
bool DirectValueArray<const T, BASE>::isReadOnly() const
{
    // Read-only!
    return true;
}

template <typename T, typename BASE>
void DirectValueArray<const T, BASE>::setValue(const T &)
{
    // Read-only!
}

template <typename T, typename BASE>
T * DirectValueArray<const T, BASE>::ptr()
{
    // Read-only!
    return nullptr;
}

template <typename T, typename BASE>
void DirectValueArray<const T, BASE>::setElement(size_t, const typename DirectValueArray<T, BASE>::ElementType &)
{
    // Read-only!
}


} // namespace cppexpose
