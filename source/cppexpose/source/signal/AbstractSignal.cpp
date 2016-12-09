
#include <cppexpose/signal/AbstractSignal.h>


namespace cppexpose
{


AbstractSignal::AbstractSignal()
: m_nextId(1)
{
}

AbstractSignal::~AbstractSignal()
{
    for (auto && pair: m_connections)
    {
        Connection & connection = pair.second;
        connection.detach();
    }
}

Connection AbstractSignal::createConnection() const
{
    Connection::Id id = m_nextId++;
    Connection connection(this, id);
    m_connections[id] = connection;

    return connection;
}

void AbstractSignal::disconnect(Connection & connection) const
{
    m_connections.erase(connection.id());
    disconnectId(connection.id());
}


} // namespace cppexpose
