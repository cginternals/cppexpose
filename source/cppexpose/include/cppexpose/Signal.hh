
#pragma once


#include <functional>
#include <unordered_map>

#include <cppexpose/AbstractSignal.hh>
#include <cppexpose/Function.hh>


namespace cppexpose
{


/**
*  @brief
*    Signal class for communicating events
*/
template <typename... Arguments>
class CPPEXPOSE_TEMPLATE_API Signal : public AbstractSignal
{
public:
    /**
    *  @brief
    *    Signature for callbacks
    */
    using Callback = std::function<void(Arguments...)>;


public:
    /**
    *  @brief
    *    Constructor
    */
    Signal();

    /**
    *  @brief
    *    Constructor that registers the signal at a parent object
    *
    *  @param[in] parent
    *    Parent object (must NOT be null!)
    *  @param[in] name
    *    Name (must NOT be empty!)
    */
    Signal(Object * parent, const std::string & name);

    /**
    *  @brief
    *    Emit signal
    *
    *  @param[in] arguments
    *    Signal arguments
    */
    void operator()(Arguments... arguments);

    /**
    *  @brief
    *    Connect signal to callback function
    *
    *  @param[in] callback
    *    Callback function that is invoked
    */
    Connection connect(Callback callback) const;

    /**
    *  @brief
    *    Connect signal to member function of an object
    *
    *  @param[in] object
    *    Object
    *  @param[in] method
    *    Member function that is invoked
    */
    template <class T, class U>
    Connection connect(T * object, void (U::*method)(Arguments...)) const;

    /**
    *  @brief
    *    Connect signal to another signal
    *
    *  @param[in] signal
    *    Signal that is invoked
    */
    Connection connect(Signal & signal) const;

    /**
    *  @brief
    *    Connect signal to a scripting function
    *
    *  @param[in] func
    *    Function that is invoked
    */
    virtual Connection connect(Function & func) const override;

    /**
    *  @brief
    *    Connect to when the signal is emitted
    *
    *  @param[in] callback
    *    Callback function that is invoked
    *
    *  @remarks
    *    This function can be used to connect a callback function
    *    to when the signal is emitted. It will be invoked just
    *    as a normal callback function, but does not contain the
    *    data of the signal.
    */
    Connection onFire(std::function<void()> callback) const;

    /**
    *  @brief
    *    Block signal
    *
    *  @remarks
    *    As long as the signal is blocked, it does not emit even if invoked
    */
    void block();

    /**
    *  @brief
    *    Unblock signal
    */
    void unblock();


protected:
    /**
    *  @brief
    *    Emit signal
    *
    *  @param[in] arguments
    *    Signal arguments
    */
    void fire(Arguments... arguments) const;

    // Virtual AbstractSignal interface
    virtual void disconnectId(Connection::Id id) const override;


protected:
    /**
    *  @brief
    *    Template for creating a variant list from typed arguments
    *
    *  @param[in] params
    *    Parameter list to build up
    *  @param[in] param
    *    First typed parameter
    *  @param[in] args
    *    More typed parameters
    */
    template <typename Type, typename... Args>
    static void buildParams(std::vector<Variant> & params, Type param, Args... args);

    /**
    *  @brief
    *    Template for creating a variant list from typed arguments
    *
    *  @param[in] params
    *    Parameter list to build up
    *  @param[in] param
    *    Typed parameter
    */
    template <typename Type>
    static void buildParams(std::vector<Variant> & params, Type param);

    /**
    *  @brief
    *    Template for creating a variant list from typed arguments
    *
    *  @param[in] params
    *    Parameter list to build up
    */
    static void buildParams(std::vector<Variant> & params);


protected:
    mutable std::unordered_map<Connection::Id, Callback> m_callbacks; ///< List of registered callbacks
    bool                                                 m_blocked;   ///< If 'true', the signal does not emit when invoked
};


} // namespace cppexpose
