
#pragma once


#include <cppexpose/type/GetType.h>
#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a type
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API BaseType : public GetType<T>::Type
{
public:
    typedef typename GetType<T>::Type::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    BaseType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~BaseType();

    // Virtual AbstractBaseType interface
    virtual std::shared_ptr<AbstractBaseType> createCopy() const override;
    virtual Variant minimum() const override;
    virtual void setMinimum(const Variant & value) override;
    virtual Variant maximum() const override;
    virtual void setMaximum(const Variant & value) override;

    // Virtual Typed interface
    virtual bool isConst() const override;
};


template <typename T>
class CPPEXPOSE_TEMPLATE_API BaseType<const T> : public GetType<T>::Type
{
public:
    typedef typename GetType<T>::Type::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    BaseType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~BaseType();

    // Virtual AbstractBaseType interface
    virtual std::shared_ptr<AbstractBaseType> createCopy() const override;
    virtual Variant minimum() const override;
    virtual void setMinimum(const Variant & value) override;
    virtual Variant maximum() const override;
    virtual void setMaximum(const Variant & value) override;

    // Virtual Typed interface
    virtual bool isConst() const override;
};


} // namespace cppexpose


#include <cppexpose/type/BaseType.inl>
