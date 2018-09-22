
#pragma once


#include <limits>

#include <cppexpose/Variant.h>
#include <cppexpose/Object.h>
#include <cppexpose/Color.h>


namespace cppexpose
{


template <typename Type>
template <typename... Args>
TypedColor<Type>::TypedColor(Args&&... args)
: ValueStorage<Type>(Type(false), std::forward<Args>(args)...)
{
}

template <typename Type>
TypedColor<Type>::~TypedColor()
{
}

template <typename Type>
VarType TypedColor<Type>::type() const
{
    return VarType::External;
}

template <typename Type>
std::string TypedColor<Type>::typeName() const
{
    return "color";
}

template <typename Type>
bool TypedColor<Type>::isNull() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::isBool() const
{
    return true;
}

template <typename Type>
bool TypedColor<Type>::isNumber() const
{
    return true;
}

template <typename Type>
bool TypedColor<Type>::isIntegral() const
{
    return true;
}

template <typename Type>
bool TypedColor<Type>::isSignedIntegral() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::isFloatingPoint() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::isEnum() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::isString() const
{
    return true;
}

template <typename Type>
bool TypedColor<Type>::isExternal() const
{
    return true;
}

template <typename Type>
bool TypedColor<Type>::isPointer() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::isObject() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::isObjectPointer() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::isArray() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::isArrayPointer() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::isFunction() const
{
    return false;
}

template <typename Type>
Variant TypedColor<Type>::minimumValue() const
{
    // Return 32bit limits
    return Variant(std::numeric_limits<std::uint32_t>::min());
}

template <typename Type>
Variant TypedColor<Type>::maximumValue() const
{
    // Return 32bit limits
    return Variant(std::numeric_limits<std::uint32_t>::max());
}

template <typename Type>
bool TypedColor<Type>::canConvertToString() const
{
    return true;
}

template <typename Type>
std::string TypedColor<Type>::toString() const
{
    return this->value().toHexString();
}

template <typename Type>
bool TypedColor<Type>::canConvertToBool() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::toBool() const
{
    return false;
}

template <typename Type>
bool TypedColor<Type>::canConvertToLongLong() const
{
    return true;
}

template <typename Type>
long long TypedColor<Type>::toLongLong() const
{
    return static_cast<long long>(this->value().argb());
}

template <typename Type>
bool TypedColor<Type>::canConvertToULongLong() const
{
    return true;
}

template <typename Type>
unsigned long long TypedColor<Type>::toULongLong() const
{
    return this->value().argb();
}

template <typename Type>
bool TypedColor<Type>::canConvertToDouble() const
{
    return false;
}

template <typename Type>
double TypedColor<Type>::toDouble() const
{
    return 0.0;
}

template <typename Type>
bool TypedColor<Type>::canConvertToObject() const
{
    return true;
}

template <typename Type>
Object TypedColor<Type>::toObject() const
{
    Object obj;
    obj.createProperty<unsigned char>("r", this->value().red());
    obj.createProperty<unsigned char>("g", this->value().green());
    obj.createProperty<unsigned char>("b", this->value().blue());
    obj.createProperty<unsigned char>("a", this->value().alpha());

    return std::move(obj);
}

template <typename Type>
bool TypedColor<Type>::canConvertToArray() const
{
    return true;
}

template <typename Type>
Array TypedColor<Type>::toArray() const
{
    Array array;
    array.createElement<unsigned char>(this->value().red());
    array.createElement<unsigned char>(this->value().green());
    array.createElement<unsigned char>(this->value().blue());
    array.createElement<unsigned char>(this->value().alpha());

    return std::move(array);
}

template <typename Type>
bool TypedColor<Type>::canConvertFromVar(const AbstractVar & value)
{
    return (value.canConvertToULongLong() ||
            value.canConvertToString()    ||
            value.isObject() || value.canConvertToObject() ||
            value.isArray() || value.canConvertToArray());
}

template <typename Type>
void TypedColor<Type>::fromVar(const AbstractVar & value)
{
    Color color;

    if (value.canConvertToULongLong()) {
        color.setArgb(value.toULongLong());
    } else if (value.canConvertToString()) {
        color.fromHexString(value.toString());
    } else if (value.isObject() || value.canConvertToObject()) {
        Object objCopy;
        Object * obj = nullptr;

        if (value.isObject()) {
            obj = value.asObject();
        } else {
            objCopy = value.toObject();
            obj = &objCopy;
        }

        if (obj) {
            if (obj->propertyExists("r"))
                color.setRed(obj->property("r")->convert<unsigned char>());
            if (obj->propertyExists("g"))
                color.setGreen(obj->property("g")->convert<unsigned char>());
            if (obj->propertyExists("b"))
                color.setBlue(obj->property("b")->convert<unsigned char>());
            if (obj->propertyExists("a"))
                color.setAlpha(obj->property("a")->convert<unsigned char>());
        }
    } else if (value.isArray() || value.canConvertToArray()) {
        Array arrCopy;
        Array * arr = nullptr;

        if (value.isArray()) {
            arr = value.asArray();
        } else {
            arrCopy = value.toArray();
            arr = &arrCopy;
        }

        if (arr) {
            if (arr->size() >= 1)
                color.setRed(arr->at(0)->convert<unsigned char>());
            if (arr->size() >= 2)
                color.setGreen(arr->at(1)->convert<unsigned char>());
            if (arr->size() >= 3)
                color.setBlue(arr->at(2)->convert<unsigned char>());
            if (arr->size() >= 4)
                color.setAlpha(arr->at(3)->convert<unsigned char>());
        }
    }

    this->setValue(color);
}

template <typename Type>
const Object * TypedColor<Type>::asObject() const
{
    return nullptr;
}

template <typename Type>
const Array * TypedColor<Type>::asArray() const
{
    return nullptr;
}


} // namespace cppexpose
