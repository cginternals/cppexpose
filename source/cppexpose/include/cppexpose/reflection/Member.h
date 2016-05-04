
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for members of an object
*/
class CPPEXPOSE_API Member
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Member();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name
    */
    Member(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Member();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Name
    */
    std::string name() const;


protected:
    std::string m_name; ///< Name of the member
};


} // namespace cppexpose
