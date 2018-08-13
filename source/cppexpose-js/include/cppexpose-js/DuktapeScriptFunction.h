
#pragma once


#include <cppexpose/AbstractFunction.h>

#include <cppexpose-js/cppexpose-js_api.h>


struct duk_hthread;
typedef struct duk_hthread duk_context;


namespace cppexpose_script
{


class DuktapeScriptBackend;


/**
*  @brief
*    Script function wrapper
*
*    This class represents a function inside the scripting environment
*    and makes it available to the reflection meta object system.
*/
class CPPEXPOSE_JS_API DuktapeScriptFunction : public cppexpose::AbstractFunction
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] scriptBackend (must NOT be null!)
    *    Duktape scripting backend
    *  @param[in] stashIndex
    *    Index of the wrapped function in the stash
    */
    DuktapeScriptFunction(DuktapeScriptBackend * scriptBackend, int stashIndex);

    // Virtual AbstractFunction interface
    virtual std::unique_ptr<AbstractFunction> clone() override;
    virtual cppexpose::Variant call(const std::vector<cppexpose::Variant> & args) override;


protected:
    DuktapeScriptBackend * m_scriptBackend; ///< Duktape scripting backend (never null)
    duk_context          * m_context;       ///< Duktape context (never null)
    int                    m_stashIndex;    ///< Index of the wrapped function in the stash
};


} // namespace cppexpose_script
