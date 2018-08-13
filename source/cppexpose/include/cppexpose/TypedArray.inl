
#pragma once


#include <algorithm>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type, typename Storage>
template <typename... Args>
TypedArray<Type, Storage>::TypedArray(Args&&... args)
: Storage(std::forward<Args>(args)...)
{
}

template <typename Type, typename Storage>
TypedArray<Type, Storage>::~TypedArray()
{
}

template <typename Type, typename Storage>
VarType TypedArray<Type, Storage>::type() const
{
    return VarType::External;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isNull() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isNumber() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isSignedIntegral() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isFloatingPoint() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isEnum() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isString() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isExternal() const
{
    return true;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isPointer() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isObject() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isArray() const
{
    // This is not an instance of Array!
    // (But it can be converted, which is what TypedArray enables on array types.)
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::isFunction() const
{
    return false;
}

template <typename Type, typename Storage>
Variant TypedArray<Type, Storage>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
Variant TypedArray<Type, Storage>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::canConvertToString() const
{
    return false;
}

template <typename Type, typename Storage>
std::string TypedArray<Type, Storage>::toString() const
{
    return "";
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::canConvertToBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::toBool() const
{
    return false;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::canConvertToLongLong() const
{
    return false;
}

template <typename Type, typename Storage>
long long TypedArray<Type, Storage>::toLongLong() const
{
    return 0ll;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::canConvertToULongLong() const
{
    return false;
}

template <typename Type, typename Storage>
unsigned long long TypedArray<Type, Storage>::toULongLong() const
{
    return 0ull;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::canConvertToDouble() const
{
    return false;
}

template <typename Type, typename Storage>
double TypedArray<Type, Storage>::toDouble() const
{
    return 0.0;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::canConvertToObject() const
{
    return false;
}

template <typename Type, typename Storage>
Object TypedArray<Type, Storage>::toObject() const
{
    return Object();
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::canConvertToArray() const
{
    return true;
}

template <typename Type, typename Storage>
Array TypedArray<Type, Storage>::toArray() const
{
    // Get element type and size of array
    using ValueType = typename Type::value_type;
    size_t numElements = std::tuple_size<Type>::value;

    // Get array
    auto const & value = this->value();

    // Create Array
    Array array;
    for (size_t i=0; i<numElements; i++) {
        array.createElement<ValueType>(value[i]);
    }

    // Return Array
    return array;
}

template <typename Type, typename Storage>
bool TypedArray<Type, Storage>::canConvertFromVar(const AbstractVar & value)
{
    return (value.hasType<Type>() || value.canConvert<Type>() || value.canConvertToArray());
}

template <typename Type, typename Storage>
void TypedArray<Type, Storage>::fromVar(const AbstractVar & value)
{
    if (value.hasType<Type>() || value.canConvert<Type>()) {
        this->setValue(value.value<Type>());
    } else if (value.isArray()) {
        // Get element type
        using ValueType = typename Type::value_type;

        // Check array
        if (!value.asArray()) {
            return;
        }

        // Get array
        const Array & arrayValue = *value.asArray();

        // Copy values into array
        Type array;
        for (size_t i=0; i<std::min(std::tuple_size<Type>::value, arrayValue.size()); i++) {
            array[i] = arrayValue.at(i)->value<ValueType>();
        }

        // Set new value
        this->setValue(array);
    } else if (value.canConvertToArray()) {
        // Get element type
        using ValueType = typename Type::value_type;

        // Convert value to generic array
        Array arrayValue = value.toArray();

        // Copy values into array
        Type array;
        for (size_t i=0; i<std::min(std::tuple_size<Type>::value, arrayValue.size()); i++) {
            array[i] = arrayValue.at(i)->value<ValueType>();
        }

        // Set new value
        this->setValue(array);
    }
}

template <typename Type, typename Storage>
const Object * TypedArray<Type, Storage>::asObject() const
{
    return nullptr;
}

template <typename Type, typename Storage>
const Array * TypedArray<Type, Storage>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
