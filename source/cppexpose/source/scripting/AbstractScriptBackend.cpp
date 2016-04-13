
#include <cppexpose/scripting/AbstractScriptBackend.h>


namespace cppexpose
{


AbstractScriptBackend::AbstractScriptBackend()
: m_scriptContext(nullptr)
{
}

AbstractScriptBackend::~AbstractScriptBackend()
{
}

ScriptContext * AbstractScriptBackend::scriptContext() const
{
    return m_scriptContext;
}


} // namespace cppexpose
