
#include "DuktapeScriptFunction.h"

#include <cppassist/memory/make_unique.h>

#include <cppexpose/scripting/ScriptContext.h>
#include <cppexpose/variant/Variant.h>

#include "DuktapeScriptBackend.h"


namespace cppexpose
{


DuktapeScriptFunction::DuktapeScriptFunction(DuktapeScriptBackend * scriptBackend, int stashIndex)
: m_scriptBackend(scriptBackend)
, m_context(scriptBackend->m_context)
, m_stashIndex(stashIndex)
{
}

std::unique_ptr<AbstractFunction> DuktapeScriptFunction::clone()
{
    return cppassist::make_unique<DuktapeScriptFunction>(m_scriptBackend, m_stashIndex);
}

Variant DuktapeScriptFunction::call(const std::vector<Variant> & args)
{
    // Get function wrapper from stash
    duk_push_global_stash(m_context);
    duk_get_prop_index(m_context, -1, m_stashIndex);

    // Push arguments
    for (Variant var : args)
    {
        m_scriptBackend->pushToDukStack(var);
    }

    // Call function
    duk_int_t error = duk_pcall(m_context, args.size());

    // Check for error
    if (error)
    {
        // Raise script exception
        m_scriptBackend->m_scriptContext->scriptException(std::string(duk_safe_to_string(m_context, -1)));
        duk_pop_2(m_context);
        return Variant();
    }

    // Convert return value
    Variant value = m_scriptBackend->fromDukStack(-1);
    duk_pop_2(m_context);
    return value;
}


} // namespace cppexpose
