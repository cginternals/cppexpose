
#pragma once


#include <type_traits>

#include <cppexpose/AbstractVar.h>


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
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] args
    *    Arguments which are passed on to the constructor of the base-var
    */
    template <typename... Args>
    AbstractTyped(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractTyped();

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
    virtual const Type & getValue() const = 0;

    /**
    *  @brief
    *    Set typed value
    *
    *  @param[in] value
    *    Typed value
    */
    virtual void setValue(const Type & value) = 0;

    // Conversion
    //   Overloaded in derived classes
};


} // namespace cppexpose


#include <cppexpose/AbstractTyped.inl>
