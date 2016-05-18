
#pragma once


#include <string>

#include <cppexpose/function/Function.h>


namespace cppexpose
{


class PropertyGroup;


/**
*  @brief
*    Representation of a method of an object
*/
class CPPEXPOSE_API Method : public Function
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] func
    *    Function object (can be null)
    *  @param[in] parent
    *    Parent object (can be null)
    */
    Method(AbstractFunction * func, PropertyGroup * parent = nullptr);

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Function name
    *  @param[in] func
    *    Function object (can be null)
    *  @param[in] parent
    *    Parent object (can be null)
    */
    Method(const std::string & name, AbstractFunction * func, PropertyGroup * parent = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Method();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Name
    */
    std::string name() const;

    /**
    *  @brief
    *    Get parent object
    *
    *  @return
    *    Parent (can be null)
    */
    PropertyGroup * parent() const;


protected:
    std::string     m_name;   ///< Name of the method
    PropertyGroup * m_parent; ///< Parent object
};


} // namespace cppexpose
