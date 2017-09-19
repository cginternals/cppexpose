
#include <cppexpose/type/type_system.h>


namespace cppexpose
{


// bool
bool Converter<bool>::canConvert()
{
    return true;
}

bool Converter<bool>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return value.toBool();
}

// char
bool Converter<char>::canConvert()
{
    return true;
}

char Converter<char>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return static_cast<char>(value.toLongLong());
}

// unsigned char
bool Converter<unsigned char>::canConvert()
{
    return true;
}

unsigned char Converter<unsigned char>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return static_cast<unsigned char>(value.toULongLong());
}

// short
bool Converter<short>::canConvert()
{
    return true;
}

short Converter<short>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return static_cast<short>(value.toLongLong());
}

// unsigned short
bool Converter<unsigned short>::canConvert()
{
    return true;
}

unsigned short Converter<unsigned short>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return static_cast<unsigned short>(value.toULongLong());
}

// int
bool Converter<int>::canConvert()
{
    return true;
}

int Converter<int>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return static_cast<int>(value.toLongLong());
}

// unsigned int
bool Converter<unsigned int>::canConvert()
{
    return true;
}

unsigned int Converter<unsigned int>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return static_cast<unsigned int>(value.toULongLong());
}

// long
bool Converter<long>::canConvert()
{
    return true;
}

long Converter<long>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return static_cast<long>(value.toLongLong());
}

// unsigned long
bool Converter<unsigned long>::canConvert()
{
    return true;
}

unsigned long Converter<unsigned long>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return static_cast<unsigned long>(value.toULongLong());
}

// long long
bool Converter<long long>::canConvert()
{
    return true;
}

long long Converter<long long>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return value.toLongLong();
}

// unsigned long long
bool Converter<unsigned long long>::canConvert()
{
    return true;
}

unsigned long long Converter<unsigned long long>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return value.toULongLong();
}

// float
bool Converter<float>::canConvert()
{
    return true;
}

float Converter<float>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return static_cast<float>(value.toDouble());
}

// double
bool Converter<double>::canConvert()
{
    return true;
}

double Converter<double>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return value.toDouble();
}

// string
bool Converter<std::string>::canConvert()
{
    return true;
}

std::string Converter<std::string>::convertTo(const cppexpose::AbstractValueContainer & value)
{
    return value.toString();
}


} // namespace cppexpose
