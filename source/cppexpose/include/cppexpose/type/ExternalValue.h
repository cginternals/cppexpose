
#pragma once


#include <functional>

#include <cppexpose/type/AbstractTypedValue.h>


namespace cppexpose
{


/**
*  @brief
*    Helper template to deduce the types for getter and setter functions
*/
template<typename T, typename Obj>
struct CPPEXPOSE_TEMPLATE_API SetterFunctions
{
    typedef T (Obj::*getter) () const;
    typedef void (Obj::*setter) (const T &);
};


/**
*  @brief
*    Typed value that is accessed via getter and setter functions
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API ExternalValue : public AbstractTypedValue<T>
{
public:
    typedef typename AbstractTypedValue<T>::ElementType ElementType;


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
    *      ExternalValue<int> value(&staticGetter, &staticSetter);
    *      ExternalValue<int> value(myValue, &MyValue::value, &MyValue::setValue);
    */
    ExternalValue(std::function<T ()> getter, std::function<void(const T &)> setter);

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
    ExternalValue(Obj * obj,
        typename SetterFunctions<T, Obj>::getter getter,
        typename SetterFunctions<T, Obj>::setter setter);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ExternalValue();

    // Virtual AbstractValue interface
    virtual std::unique_ptr<AbstractValue> createCopy() const override;
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & value) override;
    virtual bool toBool() const override;
    virtual bool fromBool(bool value) override;
    virtual long long toLongLong() const override;
    virtual bool fromLongLong(long long value) override;
    virtual unsigned long long toULongLong() const override;
    virtual bool fromULongLong(unsigned long long value) override;
    virtual double toDouble() const override;
    virtual bool fromDouble(double value) override;

    // Virtual AbstractTypedValue<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;
    virtual const T * ptr() const override;
    virtual T * ptr() override;
    virtual size_t numElements() const override;
    virtual ElementType getElement(size_t i) const override;
    virtual void setElement(size_t i, ElementType value) override;
    virtual void push(ElementType value) override;
    virtual std::vector<std::string> keys() const override;
    virtual ElementType getElement(const std::string & key) const override;
    virtual void setElement(const std::string & key, ElementType value) override;


protected:
    std::function<T ()>            m_getter; ///< Function to get the value
    std::function<void(const T &)> m_setter; ///< Function to set the value
};


} // namespace cppexpose


#include <cppexpose/type/ExternalValue.inl>
