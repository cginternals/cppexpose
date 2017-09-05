
#pragma once


namespace cppexpose
{


template <typename T>
std::map<std::string, T> EnumValues<T>::namedValues()
{
    static std::map<std::string, T> map;
    return map;
}


} // namespace cppexpose
