
#pragma once


#include <cppexpose/typed/StoredValueSingle.hh>
#include <cppexpose/typed/StoredValueArray.hh>


namespace cppexpose
{


template <typename T, typename BASE, typename = void>
struct StoredValueType
{
    using Type = StoredValueSingle<T, BASE>;
};

template <typename T, typename BASE>
struct StoredValueType<T, BASE, helper::EnableIf<helper::isArray<T>>>
{
    using Type = StoredValueArray<T, BASE>;
};


/**
*  @brief
*    Typed value (read/write) that is stored directly
*/
template <typename T, typename BASE>
class StoredValue : public StoredValueType<T, BASE>::Type
{
public:
    typedef typename StoredValueType<T, BASE>::Type BaseType;


public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    StoredValue(Args&&... args);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    StoredValue(const T & value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StoredValue();
};


} // namespace cppexpose
