
#pragma once


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127) // conditional expression is constant
#endif


namespace cppexpose
{


template <typename T, typename BASE>
TypedFloatingPoint<T, BASE>::TypedFloatingPoint()
{
}

template <typename T, typename BASE>
TypedFloatingPoint<T, BASE>::~TypedFloatingPoint()
{
}

template <typename T, typename BASE>
std::string TypedFloatingPoint<T, BASE>::typeName() const
{
         if (sizeof(T)  > sizeof(float)) return "double";
    else if (sizeof(T) == sizeof(float)) return "float";
    else                                 return "half";
}

template <typename T, typename BASE>
bool TypedFloatingPoint<T, BASE>::isFloatingPoint() const
{
    return true;
}


} // namespace cppexpose


#ifdef _MSC_VER
#pragma warning(pop)
#endif
