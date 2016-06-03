
#pragma once


#include "duktape-1.4.0/duktape.h"

#include <cppexpose/function/AbstractFunction.h>


namespace cppexpose
{


class DuktapeScriptBackend;


/**
*  @brief
*    Script function wrapper
*
*    This class represents a function inside the scripting environment
*    and makes it available to the reflection meta object system.
*/
class DuktapeScriptFunction : public AbstractFunction
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] scriptBackend
    *    Duktape scripting backend
    *  @param[in] stashFunctionIndex
    *    Index of the wrapped function on the stash
    */
    DuktapeScriptFunction(DuktapeScriptBackend * scriptBackend, int stashFunctionIndex);

    // Virtual AbstractFunction interface
    virtual AbstractFunction * clone() override;
    virtual Variant call(const std::vector<Variant> & args) override;


protected:
    DuktapeScriptBackend * m_scriptBackend;
    duk_context          * m_context;
    int                    m_stashFunctionIndex;
};


} // namespace cppexpose
