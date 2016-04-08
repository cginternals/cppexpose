
#pragma once


#include <cppexpose/typed/StoredValueSingle.h>
#include <cppexpose/typed/StoredValueArray.h>


namespace cppexpose
{


template <typename T, typename = void>
struct StoredValueType
{
    using Type = StoredValueSingle<T>;
};

template <typename T>
struct StoredValueType<T, helper::EnableIf<helper::isArray<T>>>
{
    using Type = StoredValueArray<T>;
};


/**
*  @brief
*    Typed value (read/write) that is stored directly
*/
template <typename T>
class StoredValue : public StoredValueType<T>::Type
{
public:
    typedef typename StoredValueType<T>::Type BaseType;


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


#include <cppexpose/typed/StoredValue.hpp>
