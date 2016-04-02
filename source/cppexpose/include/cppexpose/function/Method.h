
#pragma once


#include <cppexpose/function/AbstractFunction.h>


namespace cppexpose
{


/**
*  @brief
*    Base class representing a pointer to a callable function
*
*    Contains a pointer to a function, which can be either a global or static function,
*    a method of an object, or a lambda function. Using this base class, the function
*    name() can be retrieved, and the function can be called by passing Variant values
*    as the function arguments.
*/
class CPPEXPOSE_API AbstractFunction
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Function name
    */
    AbstractFunction(const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractFunction();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Function name
    */
    std::string name() const;

    /**
    *  @brief
    *    Create a copy of the function object
    *
    *  @return
    *    New function object pointing to the same function. Has to be deleted by the caller.
    */
    virtual AbstractFunction * clone() = 0;

    /**
    *  @brief
    *    Call function
    *
    *  @param[in] args
    *    List of arguments as Variants
    *
    *  @return
    *    New function object pointing to the same function. Has to be deleted by the caller.
    */
    virtual Variant call(const std::vector<Variant> & args) = 0;


protected:
    std::string m_name; ///< Function name
};


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


/**
*  @brief
*    Representation of a method
*/
template <class T, typename RET, typename... Arguments>
class Method : public AbstractFunction
{
public:
    /**
    *  @brief
    *    Typed function pointer for a member function of class T
    */
    typedef RET (T::*MethodPtr) (Arguments...);


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Function name
    *  @param[in] method
    *    Pointer to a member function of the given object obj
    */
    Method(const std::string & name, T * obj, MethodPtr method);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Method();

    // Virtual AbstractFunction interface
    virtual AbstractFunction * clone() override;
    virtual Variant call(const std::vector<Variant> & args) override;


protected:
    template<size_t... I>
    Variant callMethod(helper::Seq<I...>, const std::vector<Variant> & args);


protected:
    MethodPtr   m_method; ///< Pointer to member function of class T
    T         * m_obj;    ///< Pointer to instance of class T
};


} // namespace cppexpose


#include <cppexpose/function/Method.hpp>
