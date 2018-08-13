
#include <cppexpose-script/AbstractScriptBackend.h>


namespace cppexpose_script
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


} // namespace cppexpose_script
