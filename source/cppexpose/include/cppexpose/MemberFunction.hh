
#pragma once


#include <cppexpose/AbstractFunction.hh>
#include <cppexpose/Variant.hh>
#include <cppexpose/function_helpers.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a member function
*/
template <class Type, typename ReturnType, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API MemberFunction : public AbstractFunction
{
public:
    /**
    *  @brief
    *    Typed function pointer for a member function of class Type
    */
    typedef ReturnType (Type::*Func) (Arguments...);


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
    MemberFunction(Type * obj, Func func);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~MemberFunction();

    // Virtual AbstractFunction interface
    virtual std::unique_ptr<AbstractFunction> clone() override;
    virtual Variant call(const std::vector<Variant> & args) override;


protected:
    template<size_t... I>
    Variant callMethod(helper::Seq<I...>, const std::vector<Variant> & args);


protected:
    Type * m_obj;  ///< Pointer to instance of class Type
    Func   m_func; ///< Function object (for non-const function)
};


} // namespace cppexpose
