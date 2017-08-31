
#pragma once


namespace cppexpose
{


template <typename T>
std::map<T, std::string> EnumStrings<T>::symbolicNames()
{
    static std::map<T, std::string> map;
    return map;
}


} // namespace cppexpose
