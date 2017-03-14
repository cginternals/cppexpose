
#pragma once


#include <sstream>

#include <cppassist/string/manipulation.h>
#include <cppassist/memory/make_unique.inl>


namespace cppexpose
{


template <typename T, typename BASE>
class DirectValue;

template <typename T, typename BASE>
class StoredValue;


template <typename T, typename ET, size_t Size, typename BASE>
TypedArray<T, ET, Size, BASE>::TypedArray()
{
}


template <typename T, typename ET, size_t Size, typename BASE>
TypedArray<T, ET, Size, BASE>::TypedArray(const TypedArray & rhs)
: Typed<T, BASE>(rhs)
{
    // don't copy m_subValues which will be lazy-initialized when used
}


template <typename T, typename ET, size_t Size, typename BASE>
TypedArray<T, ET, Size, BASE>::TypedArray(TypedArray && rhs)
: Typed<T, BASE>(std::move(rhs))
, m_subValues(std::move(rhs.m_subValues))
{
}

template <typename T, typename ET, size_t Size, typename BASE>
TypedArray<T, ET, Size, BASE>::~TypedArray()
{
}


template <typename T, typename ET, size_t Size, typename BASE>
TypedArray<T, ET, Size, BASE> & TypedArray<T, ET, Size, BASE>::operator=(const TypedArray & rhs)
{
    Typed<T, BASE>::operator=(rhs);

    // don't copy m_subValues which will be lazy-initialized when used

    return *this;
}


template <typename T, typename ET, size_t Size, typename BASE>
TypedArray<T, ET, Size, BASE> & TypedArray<T, ET, Size, BASE>::operator=(TypedArray && rhs)
{
    Typed<T, BASE>::operator=(std::move(rhs));

    m_subValues = std::move(rhs.m_subValues);

    return *this;
}

template <typename T, typename ET, size_t Size, typename BASE>
size_t TypedArray<T, ET, Size, BASE>::numElements() const
{
    return Size;
}

template <typename T, typename ET, size_t Size, typename BASE>
std::string TypedArray<T, ET, Size, BASE>::typeName() const
{
    // [TODO] This is not nice and potentially expensive.
    //        Find a better way to get type names.
    DirectValue<ET> dummy;

    std::stringstream s;
    s << "array<" << dummy.typeName() << ", " << Size << ">";
    return s.str();
}

template <typename T, typename ET, size_t Size, typename BASE>
bool TypedArray<T, ET, Size, BASE>::isComposite() const
{
    return true;
}

template <typename T, typename ET, size_t Size, typename BASE>
size_t TypedArray<T, ET, Size, BASE>::numSubValues() const
{
    return Size;
}

template <typename T, typename ET, size_t Size, typename BASE>
AbstractTyped * TypedArray<T, ET, Size, BASE>::subValue(size_t index)
{
    // Create typed accessor for sub-values on first call to this function
    if (m_subValues.empty())
    {
        for (size_t i=0; i<Size; i++)
        {
            m_subValues.push_back(cppassist::make_unique<StoredValue<ET>>(
                [this, i] () -> ET {
                    return this->getElement(i);
                },
                [this, i] (const ET & value) {
                    this->setElement(i, value);
                }
            ));
        }
    }

    // Return sub-value accessor
    return (index < Size) ? m_subValues[index].get() : nullptr;
}

template <typename T, typename ET, size_t Size, typename BASE>
bool TypedArray<T, ET, Size, BASE>::isArray() const
{
    return true;
}

template <typename T, typename ET, size_t Size, typename BASE>
std::string TypedArray<T, ET, Size, BASE>::toString() const
{
    std::string str = "(";

    for (size_t i=0; i<Size; i++) {
        if (i > 0) str += ", ";
        str += const_cast<TypedArray<T, ET, Size, BASE> *>(this)->subValue(i)->toString();
    }

    str += ")";

    return str;
}

template <typename T, typename ET, size_t Size, typename BASE>
bool TypedArray<T, ET, Size, BASE>::fromString(const std::string & value)
{
    std::vector<std::string> elementStrings = cppassist::string::parseArray(value, Size);
    if (elementStrings.size() != Size) {
        return false;
    }

    for (size_t i=0; i<Size; i++)
    {
        if (!this->subValue(i)->fromString(elementStrings[i])) {
            return false;
        }
    }

    return true;
}


} // namespace cppexpose
