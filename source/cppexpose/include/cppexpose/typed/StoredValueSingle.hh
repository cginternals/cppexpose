
#pragma once


#include <functional>

#include <cppexpose/typed/GetTyped.hh>


namespace cppexpose
{


/**
*  @brief
*    Helper template to deduce the types for getter and setter functions
*/
template<typename T, typename Obj>
struct SingleValueFunctions
{
    typedef T (Obj::*getter) () const;
    typedef void (Obj::*setter) (const T &);
};


/**
*  @brief
*    Typed value (read/write) that is accessed via getter and setter functions
*/
template <typename T, typename BASE>
class StoredValueSingle : public GetTyped<T, BASE>::Type
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
    *      StoredValueSingle<int> v(&staticGetter, &staticSetter);
    *      StoredValueSingle<int> v(myValue, &MyValue::value, &MyValue::setValue);
    */
    StoredValueSingle(std::function<T ()> getter,
                      std::function<void(const T &)> setter);

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
    */
    template <typename Obj>
    StoredValueSingle(Obj * obj,
                      typename SingleValueFunctions<T, Obj>::getter getter,
                      typename SingleValueFunctions<T, Obj>::setter setter);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StoredValueSingle();

    // Virtual AbstractTyped interface
    virtual std::unique_ptr<AbstractTyped> clone() const override;

    // Virtual Typed<T> functions
    virtual T value() const override;
    virtual void setValue(const T & value) override;
    virtual const T * ptr() const override;
    virtual T * ptr() override;


protected:
    /**
    *  @brief
    *    Constructor
    */
    StoredValueSingle();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    */
    StoredValueSingle(const std::function<T ()> & getter);


protected:
    std::function<T ()>            m_getter; ///< Function to get the value
    std::function<void(const T &)> m_setter; ///< Function to set the value
};


/**
*  @brief
*    Typed value (read-only) that is accessed via getter and setter functions
*/
template <typename T, typename BASE>
class StoredValueSingle<const T, BASE> : public StoredValueSingle<T, BASE>
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    */
    StoredValueSingle(std::function<T ()> getter);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] obj
    *    Object pointer
    *  @param[in] getter
    *    Member function to get the value
    */
    template <typename Obj>
    StoredValueSingle(Obj * obj,
                      typename SingleValueFunctions<T, Obj>::getter getter);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StoredValueSingle();

    // Virtual AbstractTyped interface
    virtual std::unique_ptr<AbstractTyped> clone() const override;
    virtual bool isReadOnly() const override;

    // Virtual Typed<T> functions
    virtual void setValue(const T & value) override;
};


} // namespace cppexpose
