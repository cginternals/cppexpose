
#pragma once


#include <typeinfo>


namespace cppexpose
{


template <typename T, typename ET>
BaseTypeImplPointer<T, ET>::BaseTypeImplPointer()
{
}

template <typename T, typename ET>
BaseTypeImplPointer<T, ET>::~BaseTypeImplPointer()
{
}

template <typename T, typename ET>
const std::string & BaseTypeImplPointer<T, ET>::typeName() const
{
    static BaseType<ET> subType;
    static const auto name = std::string("pointer<") + subType.typeName() + ">";

    return name;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isNull() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isType() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isArray() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isDynamicArray() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isMap() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isBoolean() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isNumber() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isString() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isIntegral() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isUnsigned() const
{
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::isFloatingPoint() const
{
    return false;
}

template <typename T, typename ET>
const T & BaseTypeImplPointer<T, ET>::defaultValue() const
{
    static ElementType value = nullptr;

    return value;
}

template <typename T, typename ET>
std::string BaseTypeImplPointer<T, ET>::toString(const T &) const
{
    // Unsupported
    return "";
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::fromString(T &, const std::string &) const
{
    // Unsupported
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::toBool(const T &) const
{
    // Unsupported
    return false;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::fromBool(T &, bool) const
{
    // Unsupported
    return false;
}

template <typename T, typename ET>
long long BaseTypeImplPointer<T, ET>::toLongLong(const T &) const
{
    // Unsupported
    return 0ll;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::fromLongLong(T &, long long) const
{
    // Unsupported
    return false;
}

template <typename T, typename ET>
unsigned long long BaseTypeImplPointer<T, ET>::toULongLong(const T &) const
{
    // Unsupported
    return 0ull;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::fromULongLong(T &, unsigned long long) const
{
    // Unsupported
    return false;
}

template <typename T, typename ET>
double BaseTypeImplPointer<T, ET>::toDouble(const T &) const
{
    // Unsupported
    return 0.0;
}

template <typename T, typename ET>
bool BaseTypeImplPointer<T, ET>::fromDouble(T &, double) const
{
    // Unsupported
    return false;
}

template <typename T, typename ET>
size_t BaseTypeImplPointer<T, ET>::numElements(const T &) const
{
    // Unsupported
    return 1;
}

template <typename T, typename ET>
T BaseTypeImplPointer<T, ET>::getElement(const T & var, size_t i) const
{
    if (i == 0) {
        return var;
    } else {
        return defaultValue();
    }
}

template <typename T, typename ET>
void BaseTypeImplPointer<T, ET>::setElement(T & var, size_t i, T value) const
{
    if (i == 0) {
        var = value;
    }
}

template <typename T, typename ET>
void BaseTypeImplPointer<T, ET>::push(T &, T) const
{
    // Unsupported
}

template <typename T, typename ET>
std::vector<std::string> BaseTypeImplPointer<T, ET>::keys(const T &) const
{
    // Unsupported
    return std::vector<std::string>();
}

template <typename T, typename ET>
T BaseTypeImplPointer<T, ET>::getElement(const T &, const std::string &) const
{
    // Unsupported
    return this->defaultValue();
}

template <typename T, typename ET>
void BaseTypeImplPointer<T, ET>::setElement(T &, const std::string &, T) const
{
    // Unsupported
}



} // namespace cppexpose
