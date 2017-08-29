
#pragma once


#include <cppexpose/type/IType.h>


namespace cppexpose
{


class AbstractType;


/**
*  @brief
*    Abstract base class for values
*/
class CPPEXPOSE_API AbstractValue : public IType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractValue();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractValue();

    /**
    *  @brief
    *    Get type of the stored value
    *
    *  @return
    *    Type object
    */
    virtual const AbstractType & type() const = 0;
};


} // namespace cppexpose
