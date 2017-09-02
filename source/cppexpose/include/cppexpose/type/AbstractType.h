
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

    /**
    *  @brief
    *    Get type of elements
    *
    *  @return
    *    Element type
    *
    *  @remarks
    *    For array types, this returns the type of the items of the array.
    *    For all other types, the original type is returned.
    */
    virtual const AbstractType & elementType() const = 0;
};


} // namespace cppexpose
