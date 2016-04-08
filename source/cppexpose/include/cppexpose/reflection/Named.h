
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for named entities
*/
class CPPEXPOSE_API Named
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name
    */
    Named(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Named();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Name
    */
    std::string name() const;


protected:
    std::string m_name; ///< Name of the entity
};


} // namespace cppexpose
