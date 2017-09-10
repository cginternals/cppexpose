
#pragma once


#include <functional>

#include <cppexpose/value/ValueContainer.h>


namespace cppexpose
{


/**
*  @brief
*    Helper template to deduce the types for getter and setter functions
*/
template<typename T, typename ET, typename Obj>
struct CPPEXPOSE_TEMPLATE_API SetterFunctions
{
    typedef T (Obj::*getter) () const;
    typedef void (Obj::*setter) (const T &);
    typedef ET (Obj::*arrayGetter) (size_t) const;
    typedef void (Obj::*arraySetter) (size_t, const ET &);
    typedef ET (Obj::*mapGetter) (const std::string &) const;
    typedef void (Obj::*mapSetter) (const std::string &, const ET &);
};


/**
*  @brief
*    Typed value that is accessed via getter and setter functions
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API ExternalValue : public ValueContainer<T>
{
public:
    typedef typename ValueContainer<T>::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] getter
    *    Function to get the value
    *  @param[in] setter
    *    Function to set the value
    *  @param[in] arrayGetter
    *    Function to get the value of an array element
    *  @param[in] arraySetter
    *    Function to set the value of an array element
    *  @param[in] mapGetter
    *    Function to get the value of a map element
    *  @param[in] mapSetter
    *    Function to set the value of a map element
    */
    ExternalValue(
        std::function<T ()> getter,
        std::function<void(const T &)> setter,
        std::function<ElementType (size_t)> arrayGetter = nullptr,
        std::function<void(size_t, const ElementType &)> arraySetter = nullptr,
        std::function<ElementType (const std::string &)> mapGetter = nullptr,
        std::function<void(const std::string &, const ElementType &)> mapSetter = nullptr
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
    *  @param[in] arrayGetter
    *    Function to get the value of an array element
    *  @param[in] arraySetter
    *    Function to set the value of an array element
    *  @param[in] mapGetter
    *    Function to get the value of a map element
    *  @param[in] mapSetter
    *    Function to set the value of a map element
    */
    template <typename Obj>
    ExternalValue(Obj * obj,
        typename SetterFunctions<T, ElementType, Obj>::getter getter,
        typename SetterFunctions<T, ElementType, Obj>::setter setter,
        typename SetterFunctions<T, ElementType, Obj>::arrayGetter arrayGetter = {},
        typename SetterFunctions<T, ElementType, Obj>::arraySetter arraySetter = {},
        typename SetterFunctions<T, ElementType, Obj>::mapGetter mapGetter = {},
        typename SetterFunctions<T, ElementType, Obj>::mapSetter mapSetter = {});

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ExternalValue();

    // Virtual AbstractValueContainer interface
    virtual std::unique_ptr<AbstractValueContainer> createCopy() const override;
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
    virtual size_t numElements() const override;
    virtual std::vector<std::string> keys() const override;

    // Virtual ValueContainer<T> interface
    virtual T value() const override;
    virtual void setValue(const T & value) override;
    virtual const T * ptr() const override;
    virtual T * ptr() override;
    virtual ElementType elementValue(size_t i) const override;
    virtual void setElementValue(size_t i, ElementType value) override;
    virtual void push(ElementType value) override;
    virtual ElementType elementValue(const std::string & key) const override;
    virtual void setElementValue(const std::string & key, ElementType value) override;


protected:
    std::function<T ()>                                           m_getter;      ///< Function to get the value
    std::function<void(const T &)>                                m_setter;      ///< Function to set the value
    std::function<ElementType (size_t)>                           m_arrayGetter; ///< Function to get the value of an array element
    std::function<void(size_t, const ElementType &)>              m_arraySetter; ///< Function to set the value of an array element
    std::function<ElementType (const std::string &)>              m_mapGetter;   ///< Function to get the value of a map element
    std::function<void(const std::string &, const ElementType &)> m_mapSetter;   ///< Function to set the value of a map element
};


} // namespace cppexpose


#include <cppexpose/value/ExternalValue.inl>
