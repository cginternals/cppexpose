
#include <cppexpose/scripting/ScriptContext.h>

#include <cppexpose/scripting/AbstractScriptBackend.h>
#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Variant.h>

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

const std::map<std::string, Object *> & ScriptContext::globalObjects() const
{
    return m_globalObjects;
}

void ScriptContext::addGlobalObject(const std::string & name, Object * obj)
{
    // Check if there is a valid scripting backend
    if (!m_backend)
    {
        return;
    }

    // Add global object
    const auto inserted = m_globalObjects.insert(std::pair<std::string, Object *>(name, obj));
    if (inserted.second)
    {
        m_backend->addGlobalObject(name, obj);
    }
}

void ScriptContext::removeGlobalObject(const std::string & name)
{
    // Check if there is a valid scripting backend
    if (!m_backend)
    {
        return;
    }

    // Find global object
    auto it = m_globalObjects.find(name);
    if (it != m_globalObjects.end()) {
        // Remove global object
        m_globalObjects.erase(it);

        // Remove in backend
        m_backend->removeGlobalObject(name);
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
