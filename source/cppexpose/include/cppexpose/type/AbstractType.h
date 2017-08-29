
#pragma once


#include <cppexpose/type/IType.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class for data types
*/
class CPPEXPOSE_API AbstractType : public IType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractType();
};


} // namespace cppexpose
