
#pragma once


#include <string>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedObjectPointer<Type, Storage>::TypedObjectPointer(Args&&... args)
: Storage(Type(nullptr), std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedObjectPointer<Type, Storage>::~TypedObjectPointer()
{
}

template <typename Type, typename Storage>
VarType TypedObjectPointer<Type, Storage>::type() const
{
    return VarType::Pointer;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isNumber() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isEnum() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isString() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isExternal() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isPointer() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isObjectPointer() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isArray() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isArrayPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::isFunction() const
{
    return false;
}

template <typename Type, typename Storage>
Variant TypedObjectPointer<Type, Storage>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
Variant TypedObjectPointer<Type, Storage>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::canConvertToString() const
{
    return true;
}

template <typename Type, typename Storage>
std::string TypedObjectPointer<Type, Storage>::toString() const
{
    const Object * obj = this->value();

    if (obj) return obj->toString();
    else     return "{}";
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::canConvertToBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::toBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::canConvertToLongLong() const
{
    return false;
}

template <typename Type, typename Storage>
long long TypedObjectPointer<Type, Storage>::toLongLong() const
{
    return 0ll;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::canConvertToULongLong() const
{
    return true;
}

template <typename Type, typename Storage>
unsigned long long TypedObjectPointer<Type, Storage>::toULongLong() const
{
    return reinterpret_cast<unsigned long long>(reinterpret_cast<const void *>(this->value()));
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::canConvertToDouble() const
{
    return false;
}

template <typename Type, typename Storage>
double TypedObjectPointer<Type, Storage>::toDouble() const
{
    return 0.0;
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::canConvertToObject() const
{
    return true;
}

template <typename Type, typename Storage>
Object TypedObjectPointer<Type, Storage>::toObject() const
{
    const Object * obj = this->value();

    if (obj) return *obj;
    else     return Object();
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::canConvertToArray() const
{
    return false;
}

template <typename Type, typename Storage>
Array TypedObjectPointer<Type, Storage>::toArray() const
{
    return Array();
}

template <typename Type, typename Storage>
bool TypedObjectPointer<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.hasType<Type>() || value.canConvert<Type>() || value.canConvertToULongLong());
}

template <typename Type, typename Storage>
void TypedObjectPointer<Type, Storage>::fromVar(const AbstractVar & value)
{
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        this->setValue(value.convert<Type>());
    } else if (value.canConvertToULongLong()) {
        this->setValue(reinterpret_cast<Type>(reinterpret_cast<void *>(value.toULongLong())));
    }
}

template <typename Type, typename Storage>
const Object * TypedObjectPointer<Type, Storage>::asObject() const
{
    return this->value();
}

template <typename Type, typename Storage>
const Array * TypedObjectPointer<Type, Storage>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
