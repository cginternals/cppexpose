
#pragma once


#include <cassert>

#include <cppexpose/expose/Variant.h>
#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Array.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedEnum<Type, Storage>::TypedEnum(Args&&... args)
: Storage(std::forward<Args>(args)...)
{
    // Create default enum strings
    this->setStrings(EnumDefaultStrings<Type>()());
}

template <typename Type, typename Storage>
TypedEnum<Type, Storage>::~TypedEnum()
{
}

template <typename Type, typename Storage>
std::vector<std::string> TypedEnum<Type, Storage>::strings() const
{
    std::vector<std::string> strings;

    for (auto element : m_stringMap) {
        strings.push_back(element.second);
    }

    return strings;
}

template <typename Type, typename Storage>
void TypedEnum<Type, Storage>::setStrings(const std::map<Type, std::string> & pairs)
{
    // Save map of enum value -> string representation
    m_stringMap = pairs;

    // Construct reverse map (string -> enum value)
    m_enumMap.clear();
    for (const std::pair<Type, std::string> & pair : pairs)
    {
        assert(m_enumMap.count(pair.second) == 0);
        m_enumMap.insert(std::make_pair(pair.second, pair.first));
    }
}

template <typename Type, typename Storage>
VarType TypedEnum<Type, Storage>::type() const
{
    return VarType::Enum;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isNumber() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isIntegral() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isEnum() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isString() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isExternal() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isArray() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::isFunction() const
{
    return false;
}

template <typename Type, typename Storage>
Variant TypedEnum<Type, Storage>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
Variant TypedEnum<Type, Storage>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::canConvertToString() const
{
    return true;
}

template <typename Type, typename Storage>
std::string TypedEnum<Type, Storage>::toString() const
{
    // Check if value has a string representation
    const auto it = m_stringMap.find(this->value());

    // Return string representation
    if (it != m_stringMap.cend()) {
        return it->second;
    }

    // None found
    return "";
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::canConvertToBool() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::toBool() const
{
    return static_cast<bool>(this->value());
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::canConvertToLongLong() const
{
    return true;
}

template <typename Type, typename Storage>
long long TypedEnum<Type, Storage>::toLongLong() const
{
    return static_cast<long long>(this->value());
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::canConvertToULongLong() const
{
    return true;
}

template <typename Type, typename Storage>
unsigned long long TypedEnum<Type, Storage>::toULongLong() const
{
    return static_cast<unsigned long long>(this->value());
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::canConvertToDouble() const
{
    return true;
}

template <typename Type, typename Storage>
double TypedEnum<Type, Storage>::toDouble() const
{
    return static_cast<double>(this->value());
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::canConvertToObject() const
{
    return false;
}

template <typename Type, typename Storage>
Object TypedEnum<Type, Storage>::toObject() const
{
    return Object();
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::canConvertToArray() const
{
    return false;
}

template <typename Type, typename Storage>
Array TypedEnum<Type, Storage>::toArray() const
{
    return Array();
}

template <typename Type, typename Storage>
bool TypedEnum<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.hasType<Type>() || value.canConvert<Type>() ||
            value.canConvertToLongLong() ||
            value.canConvertToULongLong() ||
            value.canConvertToDouble() ||
            value.canConvertToBool() ||
            value.canConvertToString() );
}

template <typename Type, typename Storage>
void TypedEnum<Type, Storage>::fromVar(const AbstractVar & value)
{
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        this->setValue(value.value<Type>());
    } else if (value.canConvertToLongLong()) {
        this->setValue(static_cast<Type>(value.toLongLong()));
    } else if (value.canConvertToULongLong()) {
        this->setValue(static_cast<Type>(value.toULongLong()));
    } else if (value.canConvertToDouble()) {
        this->setValue(static_cast<Type>(value.toDouble()));
    } else if (value.canConvertToBool()) {
        this->setValue(static_cast<Type>(value.toBool()));
    } else if (value.canConvertToString()) {
        // Find enum of string representation
        auto it = m_enumMap.find(value.toString());
        if (it != m_enumMap.end()) {
            // Set value
            this->setValue((*it).second);
        }
    }
}


} // namespace cppexpose
