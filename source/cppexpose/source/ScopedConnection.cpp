
#include <cppexpose/ScopedConnection.h>


namespace cppexpose
{


ScopedConnection::ScopedConnection()
{
}

ScopedConnection::ScopedConnection(const Connection & connection)
: m_connection(connection)
{
}

ScopedConnection::ScopedConnection(ScopedConnection && other)
: m_connection(std::move(other.m_connection))
{
}

ScopedConnection::~ScopedConnection()
{
    m_connection.disconnect();
}

ScopedConnection & ScopedConnection::operator=(const Connection & connection)
{
    m_connection.disconnect();
    m_connection = connection;

    return *this;
}

ScopedConnection & ScopedConnection::operator=(ScopedConnection && other)
{
    m_connection.disconnect();
    m_connection = std::move(other.m_connection);

    return *this;
}


} // namespace cppexpose
