
#pragma once


#include <memory>
#include <vector>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{

class Variant;


/**
*  @brief
*    Base class for callable functions or function objects
*/
class CPPEXPOSE_API AbstractFunction
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractFunction();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractFunction();

    /**
    *  @brief
    *    Create a copy of the function object
    *
    *  @return
    *    New function object pointing to the same function. Has to be deleted by the caller.
    */
    virtual std::unique_ptr<AbstractFunction> clone() = 0;

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
};


} // namespace cppexpose
