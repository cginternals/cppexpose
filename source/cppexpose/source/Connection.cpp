
#include <cppexpose/Connection.h>

#include <cppexpose/AbstractSignal.h>


namespace cppexpose
{


Connection::Connection()
{
}

Connection::Connection(const Connection & other)
: m_state(other.m_state)
{
}

Connection::Connection(Connection && other)
: m_state(std::move(other.m_state))
{
}

Connection::Connection(const AbstractSignal * signal, Id id)
: m_state(std::make_shared<State>(signal, id))
{
}

Connection & Connection::operator=(const Connection & other)
{
    m_state = other.m_state;

    return *this;
}

Connection & Connection::operator=(Connection && other)
{
    m_state = std::move(other.m_state);

    return *this;
}

Connection::Id Connection::id() const
{
    return m_state ? m_state->id : 0;
}

void Connection::disconnect()
{
    if (m_state && m_state->signal)
    {
        m_state->signal->disconnect(*this);
        detach();
    }
}

void Connection::detach()
{
    if (m_state)
    {
        m_state->signal = nullptr;
    }
}

Connection::State::State(const AbstractSignal * signal, Id id)
: signal(signal)
, id(id)
{
}


} // namespace cppexpose
