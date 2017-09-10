
#pragma once


namespace cppexpose
{


// Generic type
template <typename T>
bool Converter<T>::canConvert()
{
    return false;
}

template <typename T>
T Converter<T>::convertTo(const cppexpose::AbstractValueContainer &)
{
    return T();
}


} // namespace cppexpose