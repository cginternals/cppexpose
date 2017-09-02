
#pragma once


namespace cppexpose
{


template <typename T>
std::map<T, std::string> EnumValues<T>::namedValues()
{
    static std::map<T, std::string> map;
    return map;
}


} // namespace cppexpose
