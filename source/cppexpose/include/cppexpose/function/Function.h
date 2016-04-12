
#pragma once


#include <string>
#include <vector>

#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


class AbstractFunction;


/**
*  @brief
*    Class representing a callable function
*
*    Contains a reference to a function, which can be either a global or static function,
*    a method of an object, a lambda function, or an arbitrary function object.
*    A Function object can be copied and duplicated, and the function can be invoked
*    with a list of Variants as arguments (making it usable in an abstract way, e.g.,
*    via GUI or scripting).
*/
class CPPEXPOSE_API Function
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Function name
    *  @param[in] func
    *    Function object (can be null)
    */
    Function(const std::string & name = "", AbstractFunction * func = nullptr);

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] other
    *    Function to copy
    */
    Function(const Function & other);

    /**
    *  @brief
    *    Destructor
    */
    ~Function();

    /**
    *  @brief
    *    Copy operator
    *
    *  @param[in] other
    *    Function to copy
    *
    *  @return
    *    Reference to this object
    */
    Function & operator=(const Function & other);

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
    *    Call function
    *
    *  @param[in] args
    *    List of arguments as Variants
    *
    *  @return
    *    Return value of the function
    */
    Variant call(const std::vector<Variant> & args);


protected:
    std::string        m_name; ///< Function name
    AbstractFunction * m_func; ///< Function implementation
};


} // namespace cppexpose
