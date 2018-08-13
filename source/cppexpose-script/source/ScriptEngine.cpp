
#include <cppexpose-script/ScriptEngine.h>

#include <cppexpose/Variant.h>


using namespace cppexpose;


namespace cppexpose_script
{


ScriptEngine::ScriptEngine()
{
}

ScriptEngine::~ScriptEngine()
{
}

const std::map<std::string, Object *> & ScriptEngine::globalObjects() const
{
    return m_globalObjects;
}

void ScriptEngine::addGlobalObject(const std::string & name, cppexpose::Object * obj)
{
    // Add global object
    const auto inserted = m_globalObjects.insert(std::pair<std::string, Object *>(name, obj));
    if (inserted.second)
    {
        onAddGlobalObject(name, obj);
    }
}

void ScriptEngine::removeGlobalObject(const std::string & name)
{
    // Find global object
    auto it = m_globalObjects.find(name);
    if (it != m_globalObjects.end()) {
        // Remove global object
        m_globalObjects.erase(it);

        // Remove in backend
        onRemoveGlobalObject(name);
    }
}

cppexpose::Variant ScriptEngine::evaluate(const std::string & code)
{
    return onEvaluate(code);
}


} // namespace cppexpose_script
