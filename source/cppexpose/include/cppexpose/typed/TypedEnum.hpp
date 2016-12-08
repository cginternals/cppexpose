
#pragma once


#include <cppexpose/typed/TypedEnum.hh>

#include <cassert>
#include <type_traits>


namespace cppexpose
{


template <typename T, typename BASE>
TypedEnum<T, BASE>::TypedEnum()
{
    // Create default enum strings
    this->setStrings(EnumDefaultStrings<T>()());
}

template <typename T, typename BASE>
TypedEnum<T, BASE>::~TypedEnum()
{
}

template <typename T, typename BASE>
std::vector<std::string> TypedEnum<T, BASE>::strings() const
{
    std::vector<std::string> strings;

    for (auto element : m_stringMap) {
        strings.push_back(element.second);
    }

    return strings;
}

template <typename T, typename BASE>
void TypedEnum<T, BASE>::setStrings(const std::map<T, std::string> & pairs)
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

template <typename T, typename BASE>
std::string TypedEnum<T, BASE>::typeName() const
{
    return "enum";
}

template <typename T, typename BASE>
bool TypedEnum<T, BASE>::isNumber() const
{
    return true;
}

template <typename T, typename BASE>
bool TypedEnum<T, BASE>::isIntegral() const
{
    return true;
}

template <typename T, typename BASE>
bool TypedEnum<T, BASE>::fromVariant(const Variant & variant)
{
    if (variant.hasType<T>()) {
        this->setValue(variant.value<T>());
    } else {
        this->setValue((T)variant.value<int>());
    }
    return true;
}

template <typename T, typename BASE>
std::string TypedEnum<T, BASE>::toString() const
{
    // Check if value has a string representation
    const auto it = m_stringMap.find(this->value());

    // Return string representation
    if (it != m_stringMap.cend()) {
        return it->second;
    }

    return "";
}

template <typename T, typename BASE>
bool TypedEnum<T, BASE>::fromString(const std::string & value)
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

template <typename T, typename BASE>
bool TypedEnum<T, BASE>::toBool() const
{
    return (bool)this->value();
}

template <typename T, typename BASE>
bool TypedEnum<T, BASE>::fromBool(bool value)
{
    this->setValue((T)value);
    return true;
}

template <typename T, typename BASE>
long long TypedEnum<T, BASE>::toLongLong() const
{
    return (long long)this->value();
}

template <typename T, typename BASE>
bool TypedEnum<T, BASE>::fromLongLong(long long value)
{
    this->setValue((T)value);
    return true;
}

template <typename T, typename BASE>
unsigned long long TypedEnum<T, BASE>::toULongLong() const
{
    return (unsigned long long)this->value();
}

template <typename T, typename BASE>
bool TypedEnum<T, BASE>::fromULongLong(unsigned long long value)
{
    this->setValue((T)value);
    return true;
}

template <typename T, typename BASE>
double TypedEnum<T, BASE>::toDouble() const
{
    return (double)this->value();
}

template <typename T, typename BASE>
bool TypedEnum<T, BASE>::fromDouble(double value)
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
