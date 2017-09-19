
#pragma once


#include <cppexpose/type/Converter.h>
#include <cppexpose/type/BaseType.h>


namespace cppexpose
{


template <typename ValueType>
bool AbstractValueContainer::canConvert() const
{
    // Check if a converter for that type exists
    return Converter<ValueType>::canConvert();
}

template <typename ValueType>
ValueType AbstractValueContainer::value() const
{
    // Check if a converter for that type exists
    if (Converter<ValueType>::canConvert())
    {
        // Convert value
        return Converter<ValueType>::convertTo(*this);
    }

    // Return default value
    static BaseType<ValueType> type;
    return type.defaultValue();
}


} // namespace cppexpose
