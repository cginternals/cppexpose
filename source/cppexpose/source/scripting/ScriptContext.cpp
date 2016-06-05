
#include <cppexpose/scripting/ScriptContext.h>

#include <cppexpose/scripting/AbstractScriptBackend.h>
#include <cppexpose/reflection/Object.h>
#include <cppexpose/variant/Variant.h>

#include "DuktapeScriptBackend.h"


namespace cppexpose
{


ScriptContext::ScriptContext(const std::string & backend)
: m_backend(nullptr)
, m_globalObject(nullptr)
{
    // Create backend

    // Javascript (duktape)
    if (backend == "duktape" || backend == "javascript" || backend == "js")
    {
        m_backend = new DuktapeScriptBackend();
        m_backend->initialize(this);
    }
}

ScriptContext::ScriptContext(AbstractScriptBackend * backend)
: m_backend(backend)
, m_globalObject(nullptr)
{
    // Register backend
    if (m_backend) {
        m_backend->initialize(this);
    }
}

ScriptContext::~ScriptContext()
{
    // Release backend
    delete m_backend;
}

PropertyGroup * ScriptContext::globalObject() const
{
    return m_globalObject;
}

void ScriptContext::setGlobalObject(PropertyGroup * obj)
{
    // Check if there is a valid scripting backend
    if (!m_backend)
    {
        return;
    }

    // Set global object
    m_globalObject = obj;
    m_backend->setGlobalObject(obj);
}

Variant ScriptContext::evaluate(const std::string & code)
{
    if (m_backend)
    {
        return m_backend->evaluate(code);
    }
    else
    {
        return Variant();
    }
}


} // namespace cppexpose
