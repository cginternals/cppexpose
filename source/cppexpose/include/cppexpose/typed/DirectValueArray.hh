
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/typed/GetTyped.hh>


namespace cppexpose
{


/**
*  @brief
*    Typed array value (read/write) that is stored directly
*/
template <typename T, typename BASE>
class CPPEXPOSE_TEMPLATE_API DirectValueArray : public GetTyped<T, BASE>::Type
{
public:
    typedef typename GetTyped<T, BASE>::Type::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    DirectValueArray();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    DirectValueArray(const T & value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DirectValueArray();

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
    T m_value;  ///< The stored value
};


/**
*  @brief
*    Typed array value (read-only) that is stored directly
*/
template <typename T, typename BASE>
class CPPEXPOSE_TEMPLATE_API DirectValueArray<const T, BASE> : public DirectValueArray<T, BASE>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    DirectValueArray();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    DirectValueArray(const T & value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DirectValueArray();

    // Virtual AbstractTyped interface
    virtual std::unique_ptr<AbstractTyped> clone() const override;
    virtual bool isReadOnly() const override;

    // Virtual Typed<T> interface
    virtual void setValue(const T & value) override;
    virtual T * ptr() override;

    // Virtual TypedArray<T> interface
    virtual void setElement(size_t i, const typename DirectValueArray<T, BASE>::ElementType & value) override;
};


} // namespace cppexpose
