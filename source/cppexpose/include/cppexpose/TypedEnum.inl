
#pragma once


#include <cassert>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedEnum<Type>::TypedEnum(Args&&... args)
: ValueStorage<Type>(std::forward<Args>(args)...)
{
    // Create default enum strings
    this->setStrings(EnumDefaultStrings<Type>()());
}

template <typename Type>
TypedEnum<Type>::~TypedEnum()
{
}

template <typename Type>
std::vector<std::string> TypedEnum<Type>::strings() const
{
    std::vector<std::string> strings;

    for (auto element : m_stringMap) {
        strings.push_back(element.second);
    }

    return strings;
}

template <typename Type>
void TypedEnum<Type>::setStrings(const std::map<Type, std::string> & pairs)
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

template <typename Type>
VarType TypedEnum<Type>::type() const
{
    return VarType::Enum;
}

template <typename Type>
bool TypedEnum<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isNumber() const
{
    return true;
}

template <typename Type>
bool TypedEnum<Type>::isIntegral() const
{
    return true;
}

template <typename Type>
bool TypedEnum<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isEnum() const
{
    return true;
}

template <typename Type>
bool TypedEnum<Type>::isString() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isExternal() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedEnum<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedEnum<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedEnum<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedEnum<Type>::canConvertToString() const
{
    return true;
}

template <typename Type>
std::string TypedEnum<Type>::toString() const
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

template <typename Type>
bool TypedEnum<Type>::canConvertToBool() const
{
    return true;
}

template <typename Type>
bool TypedEnum<Type>::toBool() const
{
    return static_cast<bool>(this->value());
}

template <typename Type>
bool TypedEnum<Type>::canConvertToLongLong() const
{
    return true;
}

template <typename Type>
long long TypedEnum<Type>::toLongLong() const
{
    return static_cast<long long>(this->value());
}

template <typename Type>
bool TypedEnum<Type>::canConvertToULongLong() const
{
    return true;
}

template <typename Type>
unsigned long long TypedEnum<Type>::toULongLong() const
{
    return static_cast<unsigned long long>(this->value());
}

template <typename Type>
bool TypedEnum<Type>::canConvertToDouble() const
{
    return true;
}

template <typename Type>
double TypedEnum<Type>::toDouble() const
{
    return static_cast<double>(this->value());
}

template <typename Type>
bool TypedEnum<Type>::canConvertToObject() const
{
    return false;
}

template <typename Type>
Object TypedEnum<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool TypedEnum<Type>::canConvertToArray() const
{
    return false;
}

template <typename Type>
Array TypedEnum<Type>::toArray() const
{
    return Array();
}

template <typename Type>
bool TypedEnum<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.hasType<Type>() || value.canConvert<Type>() ||
            value.canConvertToLongLong() ||
            value.canConvertToULongLong() ||
            value.canConvertToDouble() ||
            value.canConvertToBool() ||
            value.canConvertToString() );
}

template <typename Type>
void TypedEnum<Type>::fromVar(const AbstractVar & value)
{
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        this->setValue(value.convert<Type>());
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

template <typename Type>
const Object * TypedEnum<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedEnum<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
