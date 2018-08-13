
#include <cppexpose-script/AbstractScriptBackend.h>

#include <cppexpose/Variant.h>


using namespace cppexpose;


namespace cppexpose_script
{


AbstractScriptBackend::AbstractScriptBackend()
{
}

AbstractScriptBackend::~AbstractScriptBackend()
{
}

const std::map<std::string, Object *> & AbstractScriptBackend::globalObjects() const
{
    return m_globalObjects;
}

void AbstractScriptBackend::addGlobalObject(const std::string & name, cppexpose::Object * obj)
{
    // Add global object
    const auto inserted = m_globalObjects.insert(std::pair<std::string, Object *>(name, obj));
    if (inserted.second)
    {
        onAddGlobalObject(name, obj);
    }
}

void AbstractScriptBackend::removeGlobalObject(const std::string & name)
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

cppexpose::Variant AbstractScriptBackend::evaluate(const std::string & code)
{
    return onEvaluate(code);
}


} // namespace cppexpose_script
