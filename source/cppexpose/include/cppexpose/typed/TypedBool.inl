
#pragma once


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4800) // 'type': forcing value to bool 'true' or 'false'
#endif


namespace cppexpose
{


template <typename T, typename BASE>
TypedBool<T, BASE>::TypedBool()
{
}

template <typename T, typename BASE>
TypedBool<T, BASE>::~TypedBool()
{
}

template <typename T, typename BASE>
std::string TypedBool<T, BASE>::typeName() const
{
    return "bool";
}

template <typename T, typename BASE>
bool TypedBool<T, BASE>::isBool() const
{
    return true;
}

template <typename T, typename BASE>
std::string TypedBool<T, BASE>::toString() const
{
    return this->value() ? "true" : "false";
}

template <typename T, typename BASE>
bool TypedBool<T, BASE>::fromString(const std::string & value)
{
    this->setValue(value == "true");
    return true;
}

template <typename T, typename BASE>
bool TypedBool<T, BASE>::toBool() const
{
    return this->value();
}

template <typename T, typename BASE>
bool TypedBool<T, BASE>::fromBool(bool value)
{
    this->setValue(value);
    return true;
}

template <typename T, typename BASE>
long long TypedBool<T, BASE>::toLongLong() const
{
    return this->value() ? 1ll : 0ll;
}

template <typename T, typename BASE>
bool TypedBool<T, BASE>::fromLongLong(long long value)
{
    this->setValue((bool)value);
    return true;
}

template <typename T, typename BASE>
unsigned long long TypedBool<T, BASE>::toULongLong() const
{
    return this->value() ? 1ull : 0ull;
}

template <typename T, typename BASE>
bool TypedBool<T, BASE>::fromULongLong(unsigned long long value)
{
    this->setValue((bool)value);
    return true;
}

template <typename T, typename BASE>
double TypedBool<T, BASE>::toDouble() const
{
    return this->value() ? 1.0 : 0.0;
}

template <typename T, typename BASE>
bool TypedBool<T, BASE>::fromDouble(double value)
{
    this->setValue((bool)value);
    return true;
}


} // namespace cppexpose


#ifdef _MSC_VER
#pragma warning(pop)
#endif
