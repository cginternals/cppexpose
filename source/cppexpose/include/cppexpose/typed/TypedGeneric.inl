
#pragma once


namespace cppexpose
{


template <typename T, typename BASE>
TypedGeneric<T, BASE>::TypedGeneric()
{
}

template <typename T, typename BASE>
TypedGeneric<T, BASE>::~TypedGeneric()
{
}

template <typename T, typename BASE>
std::string TypedGeneric<T, BASE>::typeName() const
{
    return "unknown";
}


} // namespace cppexpose
