
#pragma once


#include <cppexpose/type/Converter.h>
#include <cppexpose/type/TypedType.h>


namespace cppexpose
{


template <typename ValueType>
bool AbstractValue::canConvert() const
{
    // Check if a converter for that type exists
    return Converter<ValueType>::canConvert();
}

template <typename ValueType>
ValueType AbstractValue::value() const
{
    // Check if a converter for that type exists
    if (Converter<ValueType>::canConvert())
    {
        // Convert value
        return Converter<ValueType>::convertTo(*this);
    }

    // Return default value
    TypedType<ValueType> type;
    return type.defaultValue();
}


} // namespace cppexpose
