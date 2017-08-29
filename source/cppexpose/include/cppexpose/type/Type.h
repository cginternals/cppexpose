
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
    typedef T BaseType;
    typedef T ElementType;


public:
    Type();
    virtual ~Type();

    // Virtual AbstractType interface
    virtual bool isConst() const override;
};


template <typename T>
class CPPEXPOSE_TEMPLATE_API Type<const T> : public GetType<T>::Type
{
public:
    typedef T BaseType;
    typedef T ElementType;


public:
    Type();
    virtual ~Type();

    // Virtual AbstractType interface
    virtual bool isConst() const override;
};


} // namespace cppexpose


#include <cppexpose/type/Type.inl>
