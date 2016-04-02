
#pragma once


#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Base interface for typed values
*/
class CPPEXPOSE_API AbstractTyped
{
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
    *    Get value type
    *
    *  @return
    *    Type id
    */
    virtual const std::type_info & type() const = 0;

    /**
    *  @brief
    *    Check if value is const (read-only)
    *
    *  @return
    *    'true' if value is read-only, else 'false'
    */
    virtual bool isReadOnly() const = 0;
};


} // namespace cppexpose
