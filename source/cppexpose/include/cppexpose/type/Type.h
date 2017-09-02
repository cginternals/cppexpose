
#pragma once


#include <cppexpose/type/GetType.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a type
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API Type : public GetType<T>::Type
{
public:
    typedef typename GetType<T>::Type::BaseType    BaseType;
    typedef typename GetType<T>::Type::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    Type();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Type();

    // Virtual AbstractType interface
    virtual bool isConst() const override;
};


template <typename T>
class CPPEXPOSE_TEMPLATE_API Type<const T> : public GetType<T>::Type
{
public:
    typedef typename GetType<T>::Type::BaseType    BaseType;
    typedef typename GetType<T>::Type::ElementType ElementType;


public:
    /**
    *  @brief
    *    Constructor
    */
    Type();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Type();

    // Virtual AbstractType interface
    virtual bool isConst() const override;
};


} // namespace cppexpose


#include <cppexpose/type/Type.inl>
