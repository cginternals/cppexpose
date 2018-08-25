
#pragma once


#include <string>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedObjectPointer<Type>::TypedObjectPointer(Args&&... args)
: ValueStorage<Type>(Type(nullptr), std::forward<Args>(args)...)
{
}

template <typename Type>
TypedObjectPointer<Type>::~TypedObjectPointer()
{
}

template <typename Type>
VarType TypedObjectPointer<Type>::type() const
{
    return VarType::Pointer;
}

template <typename Type>
bool TypedObjectPointer<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isNumber() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isIntegral() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isString() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isExternal() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isPointer() const
{
    return true;
}

template <typename Type>
bool TypedObjectPointer<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isObjectPointer() const
{
    return true;
}

template <typename Type>
bool TypedObjectPointer<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedObjectPointer<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedObjectPointer<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedObjectPointer<Type>::canConvertToString() const
{
    return true;
}

template <typename Type>
std::string TypedObjectPointer<Type>::toString() const
{
    const Object * obj = this->value();

    if (obj) return obj->toString();
    else     return "{}";
}

template <typename Type>
bool TypedObjectPointer<Type>::canConvertToBool() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::toBool() const
{
    return false;
}

template <typename Type>
bool TypedObjectPointer<Type>::canConvertToLongLong() const
{
    return false;
}

template <typename Type>
long long TypedObjectPointer<Type>::toLongLong() const
{
    return 0ll;
}

template <typename Type>
bool TypedObjectPointer<Type>::canConvertToULongLong() const
{
    return true;
}

template <typename Type>
unsigned long long TypedObjectPointer<Type>::toULongLong() const
{
    return reinterpret_cast<unsigned long long>(reinterpret_cast<const void *>(this->value()));
}

template <typename Type>
bool TypedObjectPointer<Type>::canConvertToDouble() const
{
    return false;
}

template <typename Type>
double TypedObjectPointer<Type>::toDouble() const
{
    return 0.0;
}

template <typename Type>
bool TypedObjectPointer<Type>::canConvertToObject() const
{
    return true;
}

template <typename Type>
Object TypedObjectPointer<Type>::toObject() const
{
    const Object * obj = this->value();

    if (obj) return *obj;
    else     return Object();
}

template <typename Type>
bool TypedObjectPointer<Type>::canConvertToArray() const
{
    return false;
}

template <typename Type>
Array TypedObjectPointer<Type>::toArray() const
{
    return Array();
}

template <typename Type>
bool TypedObjectPointer<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvert<Type>() || value.canConvertToULongLong());
}

template <typename Type>
void TypedObjectPointer<Type>::fromVar(const AbstractVar & value)
{
    if (value.canConvert<Type>()) {
        this->setValue(value.convert<Type>());
    } else if (value.canConvertToULongLong()) {
        this->setValue(reinterpret_cast<Type>(reinterpret_cast<void *>(value.toULongLong())));
    }
}

template <typename Type>
const Object * TypedObjectPointer<Type>::asObject() const
{
    return this->value();
}

template <typename Type>
const Array * TypedObjectPointer<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
