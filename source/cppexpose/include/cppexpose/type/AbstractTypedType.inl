
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


} // namespace cppexpose
