
#pragma once


#include <cppexpose/typed/TypedArray.h>

#include <functional>
#include <sstream>


namespace cppexpose
{


template <typename T>
class StoredValue;

template <typename T>
class DirectValue;


template <typename T, size_t Size, typename BaseType>
TypedArray<T, Size, BaseType>::TypedArray()
{
}

template <typename T, size_t Size, typename BaseType>
TypedArray<T, Size, BaseType>::~TypedArray()
{
    for (AbstractTyped * subValue : m_subValues)
    {
        delete subValue;
    }
}

template <typename T, size_t Size, typename BaseType>
size_t TypedArray<T, Size, BaseType>::numElements() const
{
    return Size;
}

template <typename T, size_t Size, typename BaseType>
std::string TypedArray<T, Size, BaseType>::typeName() const
{
    // [TODO] This is not nice and potentially expensive.
    //        Find a better way to get type names.
    DirectValue<T> dummy;

    std::stringstream s;
    s << "array<" << dummy.typeName() << ", " << Size << ">";
    return s.str();
}

template <typename T, size_t Size, typename BaseType>
bool TypedArray<T, Size, BaseType>::isComposite() const
{
    return true;
}

template <typename T, size_t Size, typename BaseType>
size_t TypedArray<T, Size, BaseType>::numSubValues() const
{
    return Size;
}

template <typename T, size_t Size, typename BaseType>
AbstractTyped * TypedArray<T, Size, BaseType>::subValue(size_t index)
{
    using namespace std::placeholders;

    // Create typed accessor for sub-values on first call to this function
    if (m_subValues.size() == 0)
    {
        for (size_t i=0; i<Size; i++)
        {
            // [TODO] This might pose a problem for clang. If so, the same
            // thing can be easily accomplished using lambda expressions.
            // But this is much more elegant :)
            m_subValues.push_back(new StoredValue<T>(
                std::bind( &TypedArray<T, Size, BaseType>::getElement, this, i ),
                std::bind( &TypedArray<T, Size, BaseType>::setElement, this, i, _1 )
            ));

            /* Alternative implementation
            m_subValues.push_back(new StoredValue<T>(
                [this, i] () -> T {
                    return this->getElement(i);
                },
                [this, i] (const T & value) {
                    this->setElement(i, value);
                }
            ));
            */
        }
    }

    // Return sub-value accessor
    return (index < Size) ? m_subValues[index] : nullptr;
}

template <typename T, size_t Size, typename BaseType>
bool TypedArray<T, Size, BaseType>::isArray() const
{
    return true;
}


} // namespace cppexpose
