
#pragma once


#include <memory>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractSignal;


/**
*  @brief
*    Object that represents a connection to a signal
*/
class CPPEXPOSE_API Connection
{
friend class AbstractSignal;


public:
    /**
    *  @brief
    *    Identifier type for signals
    */
    typedef unsigned int Id;


public:
    /**
    *  @brief
    *    Constructor
    */
    Connection();

    /**
    *  @brief
    *    Copy Constructor
    *
    *  @param[in] other
    *    Connection
    */
    Connection(const Connection & other);

    /**
    *  @brief
    *    Move Constructor
    *
    *  @param[in] other
    *    Connection
    */
    Connection(Connection && other);

    /**
    *  @brief
    *    Copy operator
    *
    *  @param[in] other
    *    Connection
    *
    *  @return
    *    Reference to this object
    */
    Connection & operator=(const Connection & other);

    /**
    *  @brief
    *    Move operator
    *
    *  @param[in] other
    *    Connection
    *
    *  @return
    *    Reference to this connection
    */
    Connection & operator=(Connection && other);

    /**
    *  @brief
    *    Get connection ID
    *
    *  @return
    *    Connection ID
    */
    Id id() const;

    /**
    *  @brief
    *    Close connection
    */
    void disconnect();


protected:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] signal
    *    Source signal
    *  @param[in] id
    *    Connection ID
    */
    Connection(const AbstractSignal * signal, Id id);

    /**
    *  @brief
    *    Detach connection
    */
    void detach();


protected:
    /**
    *  @brief
    *    Connection state
    */
    struct State
    {
        const AbstractSignal * signal;  ///< Source signal
        Id                     id;      ///< Connection ID
    };


protected:
    std::shared_ptr<State> m_state; ///< Connection state
};


} // namespace cppexpose
