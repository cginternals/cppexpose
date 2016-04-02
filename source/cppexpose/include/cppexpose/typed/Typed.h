
#pragma once


#include <cppexpose/typed/AbstractTyped.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a typed value
*/
template <typename T>
class Typed : public AbstractTyped
{
public:
    typedef T Type;  ///< Type of the value


public:
    /**
    *  @brief
    *    Constructor
    */
    Typed();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Typed();

    /**
    *  @brief
    *    Get value
    *
    *  @return
    *    Value
    */
    virtual T value() const = 0;

    /**
    *  @brief
    *    Set value
    *
    *  @param[in] value
    *    Value
    */
    virtual void setValue(const T & value) = 0;

    // Virtual AbstractTyped interface
    virtual const std::type_info & type() const override;
    virtual bool isReadOnly() const override;
};


} // namespace cppexpose


#include <cppexpose/typed/Typed.hpp>
