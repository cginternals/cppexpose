
#pragma once


#include <unordered_map>

#include <cppexpose/Connection.hh>


namespace cppexpose
{


class Object;
class Function;


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
    *    Constructor that registers the signal at a parent object
    *
    *  @param[in] parent
    *    Parent object (must NOT be null!)
    *  @param[in] name
    *    Name (must NOT be empty!)
    */
    AbstractSignal(Object * parent, const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractSignal();

//    virtual Connection connect(Function & func) const;


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
