
#pragma once


namespace cppexpose
{


template <typename T, typename ET>
AbstractTypedType<T, ET>::AbstractTypedType()
{
}

template <typename T, typename ET>
AbstractTypedType<T, ET>::~AbstractTypedType()
{
}

template <typename T, typename ET>
bool AbstractTypedType<T, ET>::hasSymbolicNames() const
{
    return !m_symbolicNames.empty();
}

template <typename T, typename ET>
const std::map<T, std::string> & AbstractTypedType<T, ET>::symbolicNames() const
{
    return m_symbolicNames;
}

template <typename T, typename ET>
void AbstractTypedType<T, ET>::setSymbolicNames(const std::map<T, std::string> & symbolicNames)
{
    m_symbolicNames = symbolicNames;
}

template <typename T, typename ET>
const AbstractType & AbstractTypedType<T, ET>::elementType() const
{
    static Type<ET> elementType;
    return elementType;
}


} // namespace cppexpose
