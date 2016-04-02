
#pragma once


#include <functional>

#include <cppexpose/typed/TypeSelector.h>


namespace cppexpose
{


/**
*  @brief
*    Typed value (read/write) that is accessed via getter and setter functions
*/
template <typename T>
class StoredValue : public TypeSelector<T>::Type
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    *  @param[in] setter
    *    Function to set the value
    *
    *  @remarks
    *    This creates a typed value that is accessed via getter
    *    and setter methods, which can be provided by global
    *    functions, member functions, or lambda functions.
    *
    *    Examples:
    *      StoredValue<int> v(&staticGetter, &staticSetter);
    *      StoredValue<int> v(
    *        std::bind(&MyValue::value, &myValue),
    *        std::bind(&MyValue::setValue, &myValue, _1)
    *      );
    */
    StoredValue(std::function<T ()> getter,
                std::function<void(const T &)> setter);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StoredValue();

    // Virtual Typed<T> functions
    virtual T value() const override;
    virtual void setValue(const T & value) override;


protected:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    */
    StoredValue(const std::function<T ()> & getter);


protected:
    std::function<T ()>            m_getter; ///< Function to get the value
    std::function<void(const T &)> m_setter; ///< Function to set the value
};


/**
*  @brief
*    Typed value (read-only) that is accessed via getter and setter functions
*/
template <typename T>
class StoredValue<const T> : public StoredValue<T>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    */
    StoredValue(std::function<T ()> getter);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StoredValue();

    // Virtual AbstractTyped interface
    virtual bool isReadOnly() const override;

    // Virtual Typed<T> functions
    virtual void setValue(const T & value) override;
};


} // namespace cppexpose


#include <cppexpose/typed/StoredValue.hpp>
