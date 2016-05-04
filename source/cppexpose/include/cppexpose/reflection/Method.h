
#pragma once


#include <cppexpose/reflection/Member.h>

#include <cppexpose/function/Function.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a method of an object
*/
class CPPEXPOSE_API Method : public Function, public Member
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
    Method(const std::string & name = "", AbstractFunction * func = nullptr);

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] other
    *    Method to copy
    */
    Method(const Method & other);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Method();

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
    Method & operator=(const Method & other);
};


} // namespace cppexpose
