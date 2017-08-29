
#pragma once


#include <cppexpose/type/Converter.h>
#include <cppexpose/type/Type.h>


namespace cppexpose
{


template <typename T>
bool AbstractValue::canConvert() const
{
    // Check if a converter for that type exists
    return Converter<T>::canConvert();
}

template <typename T>
T AbstractValue::value() const
{
    // Check if a converter for that type exists
    if (Converter<T>::canConvert())
    {
        // Convert value
        return Converter<T>::convertTo(*this);
    }

    // Return default value
    Type<T> type;
    return type.defaultValue();
}


} // namespace cppexpose
