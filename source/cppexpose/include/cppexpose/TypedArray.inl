
#pragma once


#include <algorithm>
#include <tuple>

#include <cppassist/string/conversion.h>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedArray<Type>::TypedArray(Args&&... args)
: ValueStorage<Type>(std::forward<Args>(args)...)
{
}

template <typename Type>
TypedArray<Type>::~TypedArray()
{
}

template <typename Type>
VarType TypedArray<Type>::type() const
{
    return VarType::External;
}

template <typename Type>
std::string TypedArray<Type>::typeName() const
{
    Var<typename Type::value_type> var;
    return "array<" + var.typeName() + "," + cppassist::string::toString<unsigned int>(std::tuple_size<Type>::value) + ">";
}

template <typename Type>
bool TypedArray<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isBool() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isNumber() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isIntegral() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isString() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isExternal() const
{
    return true;
}

template <typename Type>
bool TypedArray<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isArray() const
{
    // This is not an instance of Array!
    // (But it can be converted, which is what TypedArray enables on array types.)
    return false;
}

template <typename Type>
bool TypedArray<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedArray<Type>::minimumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
Variant TypedArray<Type>::maximumValue() const
{
    // Not supported
    return Variant();
}

template <typename Type>
bool TypedArray<Type>::canConvertToString() const
{
    return false;
}

template <typename Type>
std::string TypedArray<Type>::toString() const
{
    return "";
}

template <typename Type>
bool TypedArray<Type>::canConvertToBool() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::toBool() const
{
    return false;
}

template <typename Type>
bool TypedArray<Type>::canConvertToLongLong() const
{
    return false;
}

template <typename Type>
long long TypedArray<Type>::toLongLong() const
{
    return 0ll;
}

template <typename Type>
bool TypedArray<Type>::canConvertToULongLong() const
{
    return false;
}

template <typename Type>
unsigned long long TypedArray<Type>::toULongLong() const
{
    return 0ull;
}

template <typename Type>
bool TypedArray<Type>::canConvertToDouble() const
{
    return false;
}

template <typename Type>
double TypedArray<Type>::toDouble() const
{
    return 0.0;
}

template <typename Type>
bool TypedArray<Type>::canConvertToObject() const
{
    return false;
}

template <typename Type>
Object TypedArray<Type>::toObject() const
{
    return Object();
}

template <typename Type>
bool TypedArray<Type>::canConvertToArray() const
{
    return true;
}

template <typename Type>
Array TypedArray<Type>::toArray() const
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

template <typename Type>
bool TypedArray<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvert<Type>() || value.canConvertToArray());
}

template <typename Type>
void TypedArray<Type>::fromVar(const AbstractVar & value)
{
    if (value.canConvert<Type>()) {
        this->setValue(value.convert<Type>());
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
            array[i] = arrayValue.at(i)->convert<ValueType>();
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
            array[i] = arrayValue.at(i)->convert<ValueType>();
        }

        // Set new value
        this->setValue(array);
    }
}

template <typename Type>
const Object * TypedArray<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedArray<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
