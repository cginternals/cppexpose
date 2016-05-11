
#pragma once


#include <cppexpose/typed/DirectValueSingle.hh>
#include <cppexpose/typed/DirectValueArray.hh>


namespace cppexpose
{


template <typename T, typename BASE, typename = void>
struct DirectValueType
{
    using Type = DirectValueSingle<T, BASE>;
};

template <typename T, typename BASE>
struct DirectValueType<T, BASE, helper::EnableIf<helper::isArray<T>>>
{
    using Type = DirectValueArray<T, BASE>;
};


/**
*  @brief
*    Typed value (read/write) that is stored directly
*/
template <typename T, typename BASE>
class DirectValue : public DirectValueType<T, BASE>::Type
{
public:
    typedef typename DirectValueType<T, BASE>::Type BaseType;


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
