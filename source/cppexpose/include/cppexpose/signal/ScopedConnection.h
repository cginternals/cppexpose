
#pragma once


#include <cppexpose/signal/Connection.h>


namespace cppexpose
{


/**
*  @brief
*    Tool to maintain a connection within a certain scope
*/
class CPPEXPOSE_API ScopedConnection
{
public:
    /**
    *  @brief
    *    Constructor
    */
    ScopedConnection();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] connection
    *    Connection that is held
    */
    ScopedConnection(const Connection & connection);

    /**
    *  @brief
    *    Copy Constructor (deleted)
    */
    ScopedConnection(const ScopedConnection &) = delete;

    /**
    *  @brief
    *    Move Constructor
    *
    *  @param[in] other
    *    Scoped connection
    */
    ScopedConnection(ScopedConnection && other);

    /**
    *  @brief
    *    Destructor
    */
    ~ScopedConnection();

    /**
    *  @brief
    *    Assign connection
    *
    *  @param[in] connection
    *    Connection that is held
    */
    ScopedConnection & operator=(const Connection & connection);

    /**
    *  @brief
    *    Assignment operator (deleted)
    */
    ScopedConnection & operator=(const ScopedConnection &) = delete;

    /**
    *  @brief
    *    Move operator
    *
    *  @param[in] other
    *    Scoped connection
    *
    *  @return
    *    Reference to this object
    */
    ScopedConnection & operator=(ScopedConnection && other);


protected:
    Connection m_connection; ///< Connection that is held
};


} // namespace cppexpose
