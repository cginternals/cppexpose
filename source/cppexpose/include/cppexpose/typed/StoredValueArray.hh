
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/typed/GetTyped.hh>


namespace cppexpose
{


/**
*  @brief
*    Helper template to deduce the types for getter and setter functions
*/
template<typename T, typename ElementType, typename Obj>
struct CPPEXPOSE_TEMPLATE_API ArrayValueFunctions
{
    typedef T (Obj::*getter) () const;
    typedef void (Obj::*setter) (const T &);
    typedef ElementType (Obj::*elementGetter) (int) const;
    typedef void (Obj::*elementSetter) (int, const ElementType &);
};


/**
*  @brief
*    Typed array value (read/write) that is accessed via getter and setter functions
*/
template <typename T, typename BASE>
class CPPEXPOSE_TEMPLATE_API StoredValueArray : public GetTyped<T, BASE>::Type
{
public:
    typedef typename GetTyped<T, BASE>::Type::ElementType ElementType;


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
    *    Constructor
    *
    *  @param[in] obj
    *    Object pointer
    *  @param[in] getter
    *    Member function to get the value
    *  @param[in] setter
    *    Member function to set the value
    *  @param[in] elementGetter
    *    Member function to get an array element
    *  @param[in] elementSetter
    *    Member function to set an array element
    */
    template <typename Obj>
    StoredValueArray(Obj * obj,
                     typename ArrayValueFunctions<T, ElementType, Obj>::getter getter,
                     typename ArrayValueFunctions<T, ElementType, Obj>::setter setter,
                     typename ArrayValueFunctions<T, ElementType, Obj>::elementGetter elementGetter,
                     typename ArrayValueFunctions<T, ElementType, Obj>::elementSetter elementSetter);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StoredValueArray();

    // Virtual AbstractTyped interface
    virtual std::unique_ptr<AbstractTyped> clone() const override;

    // Virtual Typed<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;
    virtual const T * ptr() const override;
    virtual T * ptr() override;

    // Virtual TypedArray<T> interface
    virtual ElementType getElement(size_t i) const override;
    virtual void setElement(size_t i, const ElementType & value) override;


protected:
    /**
    *  @brief
    *    Constructor
    */
    StoredValueArray();

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
template <typename T, typename BASE>
class CPPEXPOSE_TEMPLATE_API StoredValueArray<const T, BASE> : public StoredValueArray<T, BASE>
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
      , std::function<typename StoredValueArray<T, BASE>::ElementType (int)> elementGetter
    );

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] obj
    *    Object pointer
    *  @param[in] getter
    *    Member function to get the value
    *  @param[in] elementGetter
    *    Member function to get an array element
    */
    template <typename Obj>
    StoredValueArray(Obj * obj,
                     typename ArrayValueFunctions<T, typename StoredValueArray<T, BASE>::ElementType, Obj>::getter getter,
                     typename ArrayValueFunctions<T, typename StoredValueArray<T, BASE>::ElementType, Obj>::elementGetter elementGetter);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StoredValueArray();

    // Virtual AbstractTyped interface
    virtual std::unique_ptr<AbstractTyped> clone() const override;
    virtual bool isReadOnly() const override;

    // Virtual Typed<T> interface
    virtual void setValue(const T & value) override;

    // Virtual TypedArray<T> interface
    virtual void setElement(size_t i, const typename StoredValueArray<T, BASE>::ElementType & value) override;
};


} // namespace cppexpose
