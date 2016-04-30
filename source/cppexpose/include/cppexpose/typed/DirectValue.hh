
#pragma once


#include <cppexpose/typed/DirectValueSingle.hh>
#include <cppexpose/typed/DirectValueArray.hh>


namespace cppexpose
{


template <typename T, typename = void>
struct DirectValueType
{
    using Type = DirectValueSingle<T>;
};

template <typename T>
struct DirectValueType<T, helper::EnableIf<helper::isArray<T>>>
{
    using Type = DirectValueArray<T>;
};


/**
*  @brief
*    Typed value (read/write) that is stored directly
*/
template <typename T>
class DirectValue : public DirectValueType<T>::Type
{
public:
    typedef typename DirectValueType<T>::Type BaseType;


public:
    /**
    *  @brief
    *    Constructor
    */
    DirectValue();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    DirectValue(const T & value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DirectValue();
};


} // namespace cppexpose
