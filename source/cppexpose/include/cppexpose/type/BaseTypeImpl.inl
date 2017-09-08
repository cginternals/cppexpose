
#pragma once


namespace cppexpose
{


template <typename T>
class BaseType;


template <typename T, typename ET>
BaseTypeImpl<T, ET>::BaseTypeImpl()
{
}

template <typename T, typename ET>
BaseTypeImpl<T, ET>::~BaseTypeImpl()
{
}

template <typename T, typename ET>
bool BaseTypeImpl<T, ET>::hasElementType() const
{
    return false;
}

template <typename T, typename ET>
std::shared_ptr<AbstractBaseType> BaseTypeImpl<T, ET>::elementType()
{
    return nullptr;
}

template <typename T, typename ET>
bool BaseTypeImpl<T, ET>::hasSymbolicNames() const
{
    return !m_namedValues.empty();
}

template <typename T, typename ET>
std::vector<std::string> BaseTypeImpl<T, ET>::symbolicNames() const
{
    std::vector<std::string> names;

    for (auto it : m_namedValues)
    {
        names.push_back(it.first);
    }

    return names;
}

template <typename T, typename ET>
const std::map<std::string, T> & BaseTypeImpl<T, ET>::namedValues() const
{
    return m_namedValues;
}

template <typename T, typename ET>
void BaseTypeImpl<T, ET>::setNamedValues(const std::map<std::string, T> & namedValues)
{
    m_namedValues = namedValues;
}


} // namespace cppexpose
