
#include <cppexpose-js/FunctionWrapper.h>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/Variant.h>

#include <cppexpose-js/Engine.h>

#include "duktape-1.4.0/duktape.h"


using namespace cppexpose;


namespace cppexpose_js
{


FunctionWrapper::FunctionWrapper(Engine * engine, int stashIndex)
: m_engine(engine)
, m_context(engine->m_context)
, m_stashIndex(stashIndex)
{
}

std::unique_ptr<AbstractFunction> FunctionWrapper::clone()
{
    return cppassist::make_unique<FunctionWrapper>(m_engine, m_stashIndex);
}

Variant FunctionWrapper::call(const std::vector<Variant> & args)
{
    // Get function wrapper from stash
    duk_push_global_stash(m_context);
    duk_get_prop_index(m_context, -1, m_stashIndex);

    // Push arguments
    for (Variant var : args)
    {
        m_engine->pushToDukStack(var);
    }

    // Call function
    duk_int_t error = duk_pcall(m_context, args.size());

    // Check for error
    if (error)
    {
        // Raise script exception
        m_engine->scriptException(std::string(duk_safe_to_string(m_context, -1)));
        duk_pop_2(m_context);
        return Variant();
    }

    // Convert return value
    Variant value = m_engine->fromDukStack(-1);
    duk_pop_2(m_context);
    return value;
}


} // namespace cppexpose_js
