
#pragma once


#include <cppexpose/typed/DirectValueSingle.h>
#include <cppexpose/typed/DirectValueArray.h>


namespace cppexpose
{


template <typename T, typename = void>
struct DirectValueBaseType
{
    using Type = DirectValueSingle<T>;
};

template <typename T>
struct DirectValueBaseType<T, helper::EnableIf<helper::isArray<T>>>
{
    using Type = DirectValueArray<T>;
};


/**
*  @brief
*    Typed value (read/write) that is stored directly
*/
template <typename T>
class DirectValue : public DirectValueBaseType<T>::Type
{
public:
    typedef typename DirectValueBaseType<T>::Type BaseType;


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


#include <cppexpose/typed/DirectValue.hpp>
