
#pragma once


namespace cppexpose
{


template <typename T, typename BASE>
TypedFilePath<T, BASE>::TypedFilePath()
{
}

template <typename T, typename BASE>
TypedFilePath<T, BASE>::~TypedFilePath()
{
}

template <typename T, typename BASE>
bool TypedFilePath<T, BASE>::isString() const
{
    return true;
}

template <typename T, typename BASE>
std::string TypedFilePath<T, BASE>::toString() const
{
    return this->value().path();
}

template <typename T, typename BASE>
bool TypedFilePath<T, BASE>::fromString(const std::string & string)
{
    this->setValue(T(string));
    return true;
}

template <typename T, typename BASE>
Variant TypedFilePath<T, BASE>::toVariant() const
{
    return Variant::fromValue<std::string>(this->toString());
}

template <typename T, typename BASE>
bool TypedFilePath<T, BASE>::fromVariant(const Variant & variant)
{
    return this->fromString(variant.value<std::string>());
}

template <typename T, typename BASE>
std::string TypedFilePath<T, BASE>::typeName() const
{
    return "filename";
}


} // namespace cppexpose
