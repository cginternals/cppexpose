
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/base/function_helpers.h>
#include <cppexpose/function/AbstractFunction.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a const member function
*/
template <class T, typename RET, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API ConstMemberFunction : public AbstractFunction
{
public:
    /**
    *  @brief
    *    Typed function pointer for a member function of class T
    */
    using Func = RET (T::*) (Arguments...) const;


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] obj
    *    Pointer to object
    *  @param[in] func
    *    Pointer to member function
    */
    ConstMemberFunction(const T * obj, Func func);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~ConstMemberFunction();

    // Virtual AbstractFunction interface
    virtual std::unique_ptr<AbstractFunction> clone() override;
    virtual Variant call(const std::vector<Variant> & args) override;


protected:
    template<size_t... I>
    Variant callMethod(helper::Seq<I...>, const std::vector<Variant> & args);


protected:
    const T * m_obj;  ///< Pointer to instance of class T
    Func      m_func; ///< Function object (for non-const function)
};


} // namespace cppexpose


#include <cppexpose/function/ConstMemberFunction.inl>
