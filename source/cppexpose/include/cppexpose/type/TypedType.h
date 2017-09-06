
#pragma once


#include <cppexpose/type/GetType.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a type
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API TypedType : public GetType<T>::Type
{
public:
    typedef typename GetType<T>::Type::BaseType    BaseType;
    typedef typename GetType<T>::Type::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    TypedType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedType();

    // Virtual AbstractType interface
    virtual std::unique_ptr<AbstractType> createCopy() const override;

    // Virtual Typed interface
    virtual bool isConst() const override;
    virtual const AbstractType & type() const override;
};


template <typename T>
class CPPEXPOSE_TEMPLATE_API TypedType<const T> : public GetType<T>::Type
{ public:
    typedef typename GetType<T>::Type::BaseType    BaseType;
    typedef typename GetType<T>::Type::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    TypedType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedType();

    // Virtual AbstractType interface
    virtual std::unique_ptr<AbstractType> createCopy() const override;

    // Virtual Typed interface
    virtual bool isConst() const override;
    virtual const AbstractType & type() const override;
};


} // namespace cppexpose


#include <cppexpose/type/TypedType.inl>
