
#pragma once


#include <cppexpose/base/function_helpers.h>
#include <cppexpose/function/AbstractFunction.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a member function
*/
template <class T, typename RET, typename... Arguments>
class MemberFunction : public AbstractFunction
{
public:
    /**
    *  @brief
    *    Typed function pointer for a member function of class T
    */
    typedef RET (T::*Func) (Arguments...);


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] obj
    *    Pointer to object
    *  @param[in] func
    *    Pointer to static function
    */
    MemberFunction(T * obj, Func func);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~MemberFunction();

    // Virtual AbstractFunction interface
    virtual AbstractFunction * clone() override;
    virtual Variant call(const std::vector<Variant> & args) override;


protected:
    template<size_t... I>
    Variant callMethod(helper::Seq<I...>, const std::vector<Variant> & args);


protected:
    T    * m_obj;  ///< Pointer to instance of class T
    Func   m_func; ///< Function object
};


} // namespace cppexpose


#include <cppexpose/function/MemberFunction.hpp>
