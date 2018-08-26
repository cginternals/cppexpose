
#pragma once


#include <type_traits>

#include <cppexpose/AbstractVar.h>
#include <cppexpose/Signal.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class for typed variables
*/
template <typename Type>
class CPPEXPOSE_TEMPLATE_API AbstractTyped : public AbstractVar
{
public:
    Signal<const Type &> valueChanged; ///< Called when the value has been changed

public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractTyped();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractTyped();

    /**
    *  @brief
    *    Access stored value
    *
    *  @return
    *    Pointer to value (should never be null!)
    */
    const Type * operator ->() const;

    /**
    *  @brief
    *    Access stored value
    *
    *  @return
    *    Pointer to value (should never be null!)
    */
    Type * operator ->();

    // Replication
    //   Overloaded in derived classes

    // Variable type
    //   Overloaded in derived classes

    // Access modifiers
    //   Overloaded in derived classes

    // Value access
    /**
    *  @brief
    *    Get typed value
    *
    *  @return
    *    Typed value
    */
    virtual const Type & value() const = 0;

    /**
    *  @brief
    *    Set typed value
    *
    *  @param[in] value
    *    Typed value
    */
    virtual void setValue(const Type & value) = 0;

    /**
    *  @brief
    *    Get pointer to value
    *
    *  @return
    *    Pointer to value (should never be null!)
    */
    virtual const Type * get() const = 0;

    /**
    *  @brief
    *    Get pointer to value
    *
    *  @return
    *    Pointer to value (should never be null!)
    */
    virtual Type * get() = 0;

    // Conversion
    //   Overloaded in derived classes
};


} // namespace cppexpose


#include <cppexpose/AbstractTyped.inl>
