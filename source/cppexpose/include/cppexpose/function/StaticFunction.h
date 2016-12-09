
#pragma once


#include <cppexpose/base/function_helpers.h>
#include <cppexpose/function/AbstractFunction.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a static function
*/
template <typename RET, typename... Arguments>
class StaticFunction : public AbstractFunction
{
public:
    /**
    *  @brief
    *    Typed function pointer for a static function
    */
    typedef RET (*Func) (Arguments...);


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] func
    *    Pointer to static function
    */
    StaticFunction(Func func);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~StaticFunction();

    // Virtual AbstractFunction interface
    virtual AbstractFunction * clone() override;
    virtual Variant call(const std::vector<Variant> & args) override;


protected:
    template<size_t... I>
    Variant callFunction(helper::Seq<I...>, const std::vector<Variant> & args);


protected:
    Func m_func; ///< Function object
};


} // namespace cppexpose


#include <cppexpose/function/StaticFunction.inl>
