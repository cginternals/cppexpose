
#pragma once


namespace cppexpose
{


template <typename T, typename ET>
BaseTypeImplContainer<T, ET>::BaseTypeImplContainer()
{
}

template <typename T, typename ET>
BaseTypeImplContainer<T, ET>::~BaseTypeImplContainer()
{
}

template <typename T, typename ET>
bool BaseTypeImplContainer<T, ET>::hasElementType() const
{
    return true;
}

template <typename T, typename ET>
std::shared_ptr<AbstractBaseType> BaseTypeImplContainer<T, ET>::elementType()
{
    if (!m_elementType)
    {
        m_elementType = std::shared_ptr<AbstractBaseType>(new BaseType<ET>());
    }

    return m_elementType;
}


} // namespace cppexpose
