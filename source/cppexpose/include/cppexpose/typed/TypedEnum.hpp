
#pragma once


#include <cppexpose/typed/TypedEnum.hh>

#include <cassert>
#include <type_traits>


namespace cppexpose
{


template <typename T>
TypedEnum<T>::TypedEnum()
{
    // Create default enum strings
    this->setStrings(EnumDefaultStrings<T>()());
}

template <typename T>
TypedEnum<T>::~TypedEnum()
{
}

template <typename T>
std::vector<std::string> TypedEnum<T>::strings() const
{
    std::vector<std::string> strings;

    for (auto element : m_stringMap) {
        strings.push_back(element.second);
    }

    return strings;
}

template <typename T>
void TypedEnum<T>::setStrings(const std::map<T, std::string> & pairs)
{
    // Save map of enum value -> string representation
    m_stringMap = pairs;

    // Construct reverse map (string -> enum value)
    m_enumMap.clear();
    for (const std::pair<T, std::string> & pair : pairs)
    {
        assert(m_enumMap.count(pair.second) == 0);
        m_enumMap.insert(std::make_pair(pair.second, pair.first));
    }
}

template <typename T>
std::string TypedEnum<T>::typeName() const
{
    return "enum";
}

template <typename T>
bool TypedEnum<T>::isNumber() const
{
    return true;
}

template <typename T>
bool TypedEnum<T>::isIntegral() const
{
    return true;
}

template <typename T>
std::string TypedEnum<T>::toString() const
{
    // Check if value has a string representation
    const auto it = m_stringMap.find(this->value());

    if (it != m_stringMap.cend()) {
        return "";
    }

    // Return string representation
    return it->second;
}

template <typename T>
bool TypedEnum<T>::fromString(const std::string & value)
{
    // Find enum of string representation
    auto it = m_enumMap.find(value);

    // Abort if it is not available
    if (it == m_enumMap.end()) {
        return false;
    }

    // Set value
    this->setValue((*it).second);
    return true;
}

template <typename T>
bool TypedEnum<T>::toBool() const
{
    return (bool)this->value();
}

template <typename T>
bool TypedEnum<T>::fromBool(bool value)
{
    this->setValue((T)value);
    return true;
}

template <typename T>
long long TypedEnum<T>::toLongLong() const
{
    return (long long)this->value();
}

template <typename T>
bool TypedEnum<T>::fromLongLong(long long value)
{
    this->setValue((T)value);
    return true;
}

template <typename T>
unsigned long long TypedEnum<T>::toULongLong() const
{
    return (unsigned long long)this->value();
}

template <typename T>
bool TypedEnum<T>::fromULongLong(unsigned long long value)
{
    this->setValue((T)value);
    return true;
}

template <typename T>
double TypedEnum<T>::toDouble() const
{
    return (double)this->value();
}

template <typename T>
bool TypedEnum<T>::fromDouble(double value)
{
    this->setValue((T)static_cast<typename std::underlying_type<T>::type>(value));
    return true;
}


template <typename T>
std::map<T, std::string> EnumDefaultStrings<T>::operator()()
{
    return std::map<T, std::string>();
}


} // namespace cppexpose
