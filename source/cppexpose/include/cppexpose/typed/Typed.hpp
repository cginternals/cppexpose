
#pragma once


#include <cppexpose/typed/Typed.h>

#include <typeinfo>


namespace cppexpose
{


template <typename T>
Typed<T>::Typed()
{
}

template <typename T>
Typed<T>::~Typed()
{
}

template <typename T>
const std::type_info & Typed<T>::type() const
{
    return typeid(T);
}

template <typename T>
bool Typed<T>::isReadOnly() const
{
    return false;
}

template <typename T>
bool Typed<T>::isComposite() const
{
    return false;
}

template <typename T>
size_t Typed<T>::numSubValues() const
{
    return 0;
}

template <typename T>
AbstractTyped * Typed<T>::subValue(size_t)
{
    return nullptr;
}

template <typename T>
bool Typed<T>::isArray() const
{
    return false;
}

template <typename T>
bool Typed<T>::isVariant() const
{
    return false;
}

template <typename T>
bool Typed<T>::isString() const
{
    return false;
}

template <typename T>
bool Typed<T>::isBool() const
{
    return false;
}

template <typename T>
bool Typed<T>::isNumber() const
{
    return false;
}

template <typename T>
bool Typed<T>::isIntegral() const
{
    return false;
}

template <typename T>
bool Typed<T>::isSignedIntegral() const
{
    return false;
}

template <typename T>
bool Typed<T>::isUnsignedIntegral() const
{
    return false;
}

template <typename T>
bool Typed<T>::isFloatingPoint() const
{
    return false;
}

template <typename T>
Variant Typed<T>::toVariant() const
{
    // [TODO] Implement!
    return Variant();
}

template <typename T>
bool Typed<T>::fromVariant(const Variant &)
{
    // [TODO] Implement!
    return false;
}

template <typename T>
std::string Typed<T>::toString() const
{
    // Unsupported for unknown types
    return "";
}

template <typename T>
bool Typed<T>::fromString(const std::string &)
{
    // Unsupported for unknown types
    return false;
}

template <typename T>
bool Typed<T>::toBool() const
{
    // Unsupported for unknown types
    return false;
}

template <typename T>
bool Typed<T>::fromBool(bool)
{
    // Unsupported for unknown types
    return false;
}

template <typename T>
long long Typed<T>::toLongLong() const
{
    // Unsupported for unknown types
    return 0ll;
}

template <typename T>
bool Typed<T>::fromLongLong(long long)
{
    // Unsupported for unknown types
    return false;
}

template <typename T>
unsigned long long Typed<T>::toULongLong() const
{
    // Unsupported for unknown types
    return 0ull;
}

template <typename T>
bool Typed<T>::fromULongLong(unsigned long long)
{
    // Unsupported for unknown types
    return false;
}

template <typename T>
double Typed<T>::toDouble() const
{
    // Unsupported for unknown types
    return 0.0;
}

template <typename T>
bool Typed<T>::fromDouble(double)
{
    // Unsupported for unknown types
    return false;
}


} // namespace cppexpose
