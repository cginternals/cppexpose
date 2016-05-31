
#pragma once


#include <cppexpose/reflection/PropertyGroup.h>
#include <cppexpose/reflection/Method.h>


namespace cppexpose
{


/**
*  @brief
*    Base class for reflection-enabled objects
*/
class CPPEXPOSE_API Object : public PropertyGroup
{


public:
    // [TODO] add before and after add/remove callbacks for functions
    //Signal<size_t, AbstractProperty *> beforeAdd;    ///< Called before a property is added to the group
    //Signal<size_t, AbstractProperty *> afterAdd;     ///< Called after a property is added to the group
    //Signal<size_t, AbstractProperty *> beforeRemove; ///< Called before a property is removed from the group
    //Signal<size_t, AbstractProperty *> afterRemove;  ///< Called after a property is removed from the group


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Name
    *  @param[in] parent
    *    Parent object (can be null)
    */
    Object(const std::string & name = "", PropertyGroup * parent = nullptr);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Object();

    /**
    *  @brief
    *    Get list of functions exported by this object
    *
    *  @return
    *    List of methods
    */
    const std::vector<Method> & functions() const;

    /**
    *  @brief
    *    Add (export) function on object
    *
    *  @param[in] name
    *    Function name
    *  @param[in] fn
    *    Function pointer
    */
    template <typename RET, typename... Arguments>
    void addFunction(const std::string & name, RET (*fn)(Arguments...));

    /**
    *  @brief
    *    Add (export) method on object
    *
    *  @param[in] name
    *    Function name
    *  @param[in] obj
    *    Pointer to object instance
    *  @param[in] member
    *    Method pointer
    */
    template <class T, typename RET, typename... Arguments>
    void addFunction(const std::string & name, T * obj, RET (T::*fn)(Arguments...));


protected:
    std::vector<Method> m_functions; ///< List of exported functions
};


} // namespace cppexpose


#include <cppexpose/reflection/Object.hpp>
