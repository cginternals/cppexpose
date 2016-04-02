
#pragma once


#include <cppexpose/function/AbstractFunction.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a static function
*/
template <typename RET, typename... Arguments>
class Function : public AbstractFunction
{
public:
    /**
    *  @brief
    *    Typed function pointer for a static function
    */
    typedef RET (*FuncPtr) (Arguments...);


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Function name
    *  @param[in] func
    *    Pointer to a static function
    */
    Function(const std::string & name, FuncPtr func);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Function();

    // Virtual AbstractFunction interface
    virtual AbstractFunction * clone() override;
    virtual Variant call(const std::vector<Variant> & args) override;


protected:
    template<size_t... I>
    Variant callFunction(helper::Seq<I...>, const std::vector<Variant> & args);


protected:
    FuncPtr m_func; ///< Pointer to static function
};


} // namespace cppexpose


#include <cppexpose/function/Function.hpp>
