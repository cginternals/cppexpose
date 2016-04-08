
#pragma once


#include <cppexpose/typed/TypeSelector.h>


namespace cppexpose
{


/**
*  @brief
*    Typed array value (read/write) that is accessed via getter and setter functions
*/
template <typename T>
class StoredValueArray : public TypeSelector<T>::Type
{
public:
    typedef typename TypeSelector<T>::Type::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    *  @param[in] setter
    *    Function to set the value
    *  @param[in] elementGetter
    *    Function to get an array element
    *  @param[in] elementSetter
    *    Function to set an array element
    */
    StoredValueArray(
        std::function<T ()> getter
      , std::function<void(const T &)> setter
      , std::function<ElementType (int)> elementGetter
      , std::function<void(int, const ElementType &)> elementSetter
    );

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StoredValueArray();

    // Virtual AbstractTyped interface
    virtual AbstractTyped * clone() const override;

    // Virtual Typed<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;

    // Virtual TypedArray<T> interface
    virtual ElementType getElement(size_t i) const override;
    virtual void setElement(size_t i, const ElementType & value) override;


protected:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    *  @param[in] elementGetter
    *    Function to get an array element
    */
    StoredValueArray(
        std::function<T ()> getter
      , std::function<ElementType (int)> elementGetter
    );


protected:
    std::function<T ()>                           m_getter;        ///< Function to get the value
    std::function<void(const T &)>                m_setter;        ///< Function to set the value
    std::function<ElementType (int)>              m_elementGetter; ///< Function to get an array element
    std::function<void(int, const ElementType &)> m_elementSetter; ///< Function to set an array element
};


/**
*  @brief
*    Typed array value (read-only) that is accessed via getter and setter functions
*/
template <typename T>
class StoredValueArray<const T> : public StoredValueArray<T>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    *  @param[in] elementGetter
    *    Function to get an array element
    */
    StoredValueArray(
        std::function<T ()> getter
      , std::function<typename StoredValueArray<T>::ElementType (int)> elementGetter
    );

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StoredValueArray();

    // Virtual AbstractTyped interface
    virtual AbstractTyped * clone() const override;
    virtual bool isReadOnly() const override;

    // Virtual Typed<T> interface
    virtual void setValue(const T & value) override;

    // Virtual TypedArray<T> interface
    virtual void setElement(size_t i, const typename StoredValueArray<T>::ElementType & value) override;
};


} // namespace cppexpose


#include <cppexpose/typed/StoredValueArray.hpp>
