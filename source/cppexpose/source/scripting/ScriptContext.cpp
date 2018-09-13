
#include <cppexpose/scripting/ScriptContext.h>

#include <cppexpose/reflection/Object.h>
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
        m_backend = cppassist::make_unique<DuktapeScriptBackend>();
        m_backend->initialize(this);
    }
}

ScriptContext::ScriptContext(std::unique_ptr<AbstractScriptBackend> && backend)
: m_backend(std::move(backend))
{
    // Register backend
    if (m_backend) {
        m_backend->initialize(this);
    }
}

ScriptContext::~ScriptContext()
{
}

const std::set<Object *> & ScriptContext::globalObjects() const
{
    return m_globalObjects;
}

void ScriptContext::addGlobalObject(Object * obj)
{
    // Check if there is a valid scripting backend
    if (!m_backend)
    {
        return;
    }

    // Add global object
    const auto inserted = m_globalObjects.insert(obj);
    if (inserted.second)
    {
        m_backend->addGlobalObject(obj);
    }
}

void ScriptContext::removeGlobalObject(Object * obj)
{
    // Check if there is a valid scripting backend
    if (!m_backend)
    {
        return;
    }

    // Remove global object
    const auto removed = m_globalObjects.erase(obj);
    if (removed > 0)
    {
        m_backend->removeGlobalObject(obj);
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
