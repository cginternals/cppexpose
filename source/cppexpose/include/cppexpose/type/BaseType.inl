
#pragma once


#include <cppassist/memory/make_unique.h>


namespace cppexpose
{


// BaseType<T>
template <typename T>
BaseType<T>::BaseType()
{
}

template <typename T>
BaseType<T>::~BaseType()
{
}

template <typename T>
std::shared_ptr<AbstractBaseType> BaseType<T>::createCopy() const
{
    return std::shared_ptr<AbstractBaseType>(new BaseType<T>);
}

template <typename T>
Variant BaseType<T>::minimum() const
{
    return Variant::fromValue(this->minimumValue());
}

template <typename T>
void BaseType<T>::setMinimum(const Variant & value)
{
    this->setMinimumValue(value.value<T>());
}

template <typename T>
Variant BaseType<T>::maximum() const
{
    return Variant::fromValue(this->maximumValue());
}

template <typename T>
void BaseType<T>::setMaximum(const Variant & value)
{
    this->setMaximumValue(value.value<T>());
}

template <typename T>
bool BaseType<T>::isConst() const
{
    return false;
}

template <typename T>
std::string BaseType<T>::toString(const T & var) const
{
    if (!this->m_namedValues.empty())
    {
        for (auto & it : this->m_namedValues)
        {
            if (var == it.second) {
                return it.first;
            }
        }
    }

    return GetType<T>::Type::toString(var);
}

template <typename T>
bool BaseType<T>::fromString(T & var, const std::string & value) const
{
    if (!this->m_namedValues.empty())
    {
        auto it = this->m_namedValues.find(value);
        if (it != this->m_namedValues.end())
        {
            var = it->second;
            return true;
        }
    }

    return GetType<T>::Type::fromString(var, value);
}


// BaseType<const T>
template <typename T>
BaseType<const T>::BaseType()
{
}

template <typename T>
BaseType<const T>::~BaseType()
{
}

template <typename T>
std::shared_ptr<AbstractBaseType> BaseType<const T>::createCopy() const
{
    return std::shared_ptr<AbstractBaseType>(new BaseType<const T>);
}

template <typename T>
Variant BaseType<const T>::minimum() const
{
    return Variant(this->minimumValue());
}

template <typename T>
void BaseType<const T>::setMinimum(const Variant & value)
{
    this->setMinimumValue(value.value<T>());
}

template <typename T>
Variant BaseType<const T>::maximum() const
{
    return Variant(this->maximumValue());
}

template <typename T>
void BaseType<const T>::setMaximum(const Variant & value)
{
    this->setMaximumValue(value.value<T>());
}

template <typename T>
bool BaseType<const T>::isConst() const
{
    return true;
}


} // namespace cppexpose
