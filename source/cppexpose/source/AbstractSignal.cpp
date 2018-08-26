
#include <cppexpose/AbstractSignal.h>

#include <cppexpose/Object.h>


namespace cppexpose
{


AbstractSignal::AbstractSignal()
: m_nextId(1)
{
}

AbstractSignal::AbstractSignal(Object * parent, const std::string & name)
: m_nextId(1)
{
    // Register signal in object
    if (parent && name != "") {
        parent->addSignal(name, this);
    }
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
