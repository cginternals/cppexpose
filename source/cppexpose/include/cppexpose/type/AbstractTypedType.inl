
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
const AbstractType & AbstractTypedType<T, ET>::elementType() const
{
    static Type<ET> elementType;
    return elementType;
}

template <typename T, typename ET>
bool AbstractTypedType<T, ET>::hasSymbolicNames() const
{
    return !m_namedValues.empty();
}

template <typename T, typename ET>
std::vector<std::string> AbstractTypedType<T, ET>::symbolicNames() const
{
    std::vector<std::string> names;

    for (auto it : m_namedValues)
    {
        names.push_back(it.first);
    }

    return names;
}

template <typename T, typename ET>
const std::map<std::string, T> & AbstractTypedType<T, ET>::namedValues() const
{
    return m_namedValues;
}

template <typename T, typename ET>
void AbstractTypedType<T, ET>::setNamedValues(const std::map<std::string, T> & namedValues)
{
    m_namedValues = namedValues;
}


} // namespace cppexpose
