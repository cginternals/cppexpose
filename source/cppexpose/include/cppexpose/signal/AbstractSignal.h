
#pragma once


#include <unordered_map>

#include <cppexpose/signal/Connection.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class for signals
*/
class CPPEXPOSE_API AbstractSignal
{
friend class Connection;


public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractSignal();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractSignal();


protected:
    /**
    *  @brief
    *    Create new empty connection
    *
    *  @return
    *    Connection
    */
    Connection createConnection() const;

    /**
    *  @brief
    *    Disconnect connection
    *
    *  @param[in] connection
    *    Connection
    */
    void disconnect(Connection & connection) const;

    /**
    *  @brief
    *    Disconnect connection by ID
    *
    *  @param[in] id
    *    Connection ID
    */
    virtual void disconnectId(Connection::Id id) const = 0;


protected:
    mutable Connection::Id                                 m_nextId;      ///< Next free connection ID
    mutable std::unordered_map<Connection::Id, Connection> m_connections; ///< Map of connections by ID
};


} // namespace cppexpose
