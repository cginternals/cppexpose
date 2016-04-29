
#pragma once


#include <cppexpose/typed/TypedArray.h>

#include <sstream>

#include <cppexpose/base/string_helpers.h>


namespace cppexpose
{


template <typename T>
class DirectValue;

template <typename T>
class StoredValue;


template <typename T, typename ET, size_t Size>
TypedArray<T, ET, Size>::TypedArray()
{
}

template <typename T, typename ET, size_t Size>
TypedArray<T, ET, Size>::~TypedArray()
{
    for (AbstractTyped * subValue : m_subValues)
    {
        delete subValue;
    }
}

template <typename T, typename ET, size_t Size>
size_t TypedArray<T, ET, Size>::numElements() const
{
    return Size;
}

template <typename T, typename ET, size_t Size>
std::string TypedArray<T, ET, Size>::typeName() const
{
    // [TODO] This is not nice and potentially expensive.
    //        Find a better way to get type names.
    DirectValue<ET> dummy;

    std::stringstream s;
    s << "array<" << dummy.typeName() << ", " << Size << ">";
    return s.str();
}

template <typename T, typename ET, size_t Size>
bool TypedArray<T, ET, Size>::isComposite() const
{
    return true;
}

template <typename T, typename ET, size_t Size>
size_t TypedArray<T, ET, Size>::numSubValues() const
{
    return Size;
}

template <typename T, typename ET, size_t Size>
AbstractTyped * TypedArray<T, ET, Size>::subValue(size_t index)
{
    // Create typed accessor for sub-values on first call to this function
    if (m_subValues.size() == 0)
    {
        for (size_t i=0; i<Size; i++)
        {
            m_subValues.push_back(new StoredValue<ET>(
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
    return (index < Size) ? m_subValues[index] : nullptr;
}

template <typename T, typename ET, size_t Size>
bool TypedArray<T, ET, Size>::isArray() const
{
    return true;
}

template <typename T, typename ET, size_t Size>
std::string TypedArray<T, ET, Size>::toString() const
{
    std::string str = "(";

    for (size_t i=0; i<Size; i++) {
        if (i > 0) str += ", ";
        str += const_cast<TypedArray<T, ET, Size> *>(this)->subValue(i)->toString();
    }

    str += ")";

    return str;
}

template <typename T, typename ET, size_t Size>
bool TypedArray<T, ET, Size>::fromString(const std::string & value)
{
    std::vector<std::string> elementStrings = helper::parseArray(value, Size);
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
