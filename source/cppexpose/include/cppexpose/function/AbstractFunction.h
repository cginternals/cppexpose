
#pragma once


#include <string>
#include <vector>
#include <functional>

#include <cppexpose/base/template_helpers.h>
#include <cppexpose/base/function_helpers.h>
#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


/**
*  @brief
*    Base class representing a reference to a callable function
*
*    Contains a reference to a function, which can be either a global or static function,
*    a method of an object, or a lambda function. Using this base class, the function
*    name() can be retrieved, and the function can be called by passing Variant values
*    as the function arguments.
*/
class CPPEXPOSE_API AbstractFunction
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Function name
    */
    AbstractFunction(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractFunction();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Function name
    */
    std::string name() const;

    /**
    *  @brief
    *    Create a copy of the function object
    *
    *  @return
    *    New function object pointing to the same function. Has to be deleted by the caller.
    */
    virtual AbstractFunction * clone() = 0;

    /**
    *  @brief
    *    Call function
    *
    *  @param[in] args
    *    List of arguments as Variants
    *
    *  @return
    *    New function object pointing to the same function. Has to be deleted by the caller.
    */
    virtual Variant call(const std::vector<Variant> & args) = 0;


protected:
    std::string m_name; ///< Function name
};


} // namespace cppexpose
