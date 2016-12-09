
#pragma once


namespace
{


template <typename T>
struct ConvertTyped
{
    static bool canConvert() {
        return false;
    }

    static T convertTo(const cppexpose::AbstractTyped &) {
        return T();
    }
};

template <>
struct ConvertTyped<bool>
{
    static bool canConvert() {
        return true;
    }

    static bool convertTo(const cppexpose::AbstractTyped & typed) {
        return typed.toBool();
    }
};

template <>
struct ConvertTyped<char>
{
    static bool canConvert() {
        return true;
    }

    static char convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<char>(typed.toLongLong());
    }
};

template <>
struct ConvertTyped<unsigned char>
{
    static bool canConvert() {
        return true;
    }

    static unsigned char convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<unsigned char>(typed.toULongLong());
    }
};

template <>
struct ConvertTyped<short>
{
    static bool canConvert() {
        return true;
    }

    static short convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<short>(typed.toLongLong());
    }
};

template <>
struct ConvertTyped<unsigned short>
{
    static bool canConvert() {
        return true;
    }

    static unsigned short convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<unsigned short>(typed.toULongLong());
    }
};

template <>
struct ConvertTyped<int>
{
    static bool canConvert() {
        return true;
    }

    static int convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<int>(typed.toLongLong());
    }
};

template <>
struct ConvertTyped<unsigned int>
{
    static bool canConvert() {
        return true;
    }

    static unsigned int convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<unsigned int>(typed.toULongLong());
    }
};

template <>
struct ConvertTyped<long>
{
    static bool canConvert() {
        return true;
    }

    static long convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<long>(typed.toLongLong());
    }
};

template <>
struct ConvertTyped<unsigned long>
{
    static bool canConvert() {
        return true;
    }

    static unsigned long convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<unsigned long>(typed.toULongLong());
    }
};

template <>
struct ConvertTyped<long long>
{
    static bool canConvert() {
        return true;
    }

    static long long convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<long long>(typed.toLongLong());
    }
};

template <>
struct ConvertTyped<unsigned long long>
{
    static bool canConvert() {
        return true;
    }

    static unsigned long long convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<unsigned long long>(typed.toULongLong());
    }
};

template <>
struct ConvertTyped<float>
{
    static bool canConvert() {
        return true;
    }

    static float convertTo(const cppexpose::AbstractTyped & typed) {
        return static_cast<float>(typed.toDouble());
    }
};

template <>
struct ConvertTyped<double>
{
    static bool canConvert() {
        return true;
    }

    static double convertTo(const cppexpose::AbstractTyped & typed) {
        return typed.toDouble();
    }
};

template <>
struct ConvertTyped<std::string>
{
    static bool canConvert() {
        return true;
    }

    static std::string convertTo(const cppexpose::AbstractTyped & typed) {
        return typed.toString();
    }
};


} // namespace


namespace cppexpose
{


template <typename T>
bool AbstractTyped::canConvert() const
{
    return ConvertTyped<T>::canConvert();
}

template <typename T>
T AbstractTyped::convert(const T & defaultValue) const
{
    // Is the target type supported? (does not guarantee successfull conversion!)
    if (ConvertTyped<T>::canConvert())
    {
        return ConvertTyped<T>::convertTo(*this);
    }

    // No conversion possible
    return defaultValue;
}


} // namespace cppexpose
