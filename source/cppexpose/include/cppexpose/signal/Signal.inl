
#pragma once


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4505) // 'identifier': unreferenced local function has been removed
#endif


namespace cppexpose
{


template <typename... Arguments>
Signal<Arguments...>::Signal()
: m_blocked(false)
{
}

template <typename... Arguments>
void Signal<Arguments...>::operator()(Arguments... arguments)
{
    fire(arguments...);
}

template <typename... Arguments>
Connection Signal<Arguments...>::connect(Callback callback) const
{
    Connection connection = createConnection();
    m_callbacks[connection.id()] = callback;
    return connection;
}

template <typename... Arguments>
template <class T, class U>
Connection Signal<Arguments...>::connect(T * object, void (U::*method)(Arguments...)) const
{
    return connect([object, method](Arguments... arguments)
    {
        (object->*method)(arguments...);
    });
}

template <typename... Arguments>
Connection Signal<Arguments...>::connect(Signal & signal) const
{
    return connect([&signal](Arguments... arguments)
    {
        signal.fire(arguments...);
    });
}

template <typename... Arguments>
Connection Signal<Arguments...>::onFire(std::function<void()> callback) const
{
    return connect([callback](Arguments...)
    {
        callback();
    });
}

template <typename... Arguments>
void Signal<Arguments...>::block()
{
    m_blocked = true;
}

template <typename... Arguments>
void Signal<Arguments...>::unblock()
{
    m_blocked = false;
}

template <typename... Arguments>
void Signal<Arguments...>::fire(Arguments... arguments) const
{
    if (m_blocked) {
        return;
    }

    for (auto & pair : m_callbacks)
    {
        Callback callback = pair.second;
        callback(arguments...);
    }
}

template <typename... Arguments>
void Signal<Arguments...>::disconnectId(Connection::Id id) const
{
    m_callbacks.erase(id);
}


} // namespace cppexpose


#ifdef _MSC_VER
#pragma warning(pop)
#endif
