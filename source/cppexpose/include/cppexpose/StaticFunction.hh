
#pragma once


#include <cppexpose/AbstractFunction.hh>
#include <cppexpose/Variant.hh>
#include <cppexpose/function_helpers.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a static function
*/
template <typename ReturnType, typename... Arguments>
class CPPEXPOSE_TEMPLATE_API StaticFunction : public AbstractFunction
{
public:
    /**
    *  @brief
    *    Typed function pointer for a static function
    */
    typedef ReturnType (*Func) (Arguments...);


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
    virtual std::unique_ptr<AbstractFunction> clone() override;
    virtual Variant call(const std::vector<Variant> & args) override;


protected:
    template<size_t... I>
    Variant callFunction(helper::Seq<I...>, const std::vector<Variant> & args);


protected:
    Func m_func; ///< Function object
};


} // namespace cppexpose
