
#include <cppexpose/scripting/ScriptContext.h>

#include <cppexpose/scripting/AbstractScriptBackend.h>
#include <cppexpose/variant/Variant.h>

#include "DuktapeScriptBackend.h"


namespace cppexpose
{


ScriptContext::ScriptContext(const std::string & backend)
: m_backend(nullptr)
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

void ScriptContext::setGlobalNamespace(const std::string & name)
{
    if (m_backend)
    {
        m_backend->setGlobalNamespace(name);
    }
}

void ScriptContext::registerObject(PropertyGroup * obj)
{
    if (m_backend)
    {
        m_backend->registerObject(obj);
    }
}

void ScriptContext::unregisterObject(PropertyGroup * obj)
{
    if (m_backend)
    {
        m_backend->unregisterObject(obj);
    }
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
