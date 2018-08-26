
#pragma once


namespace cppexpose
{


template <typename... Arguments>
Signal<Arguments...>::Signal()
: m_blocked(false)
{
}

template <typename... Arguments>
Signal<Arguments...>::Signal(Object * parent, const std::string & name)
: AbstractSignal(parent, name)
, m_blocked(false)
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
Connection Signal<Arguments...>::connect(Function & func) const
{
    // Save callback function
    Function function = func;

    // Connect to signal
    return this->connect([function](Arguments... arguments)
    {
        // Set arguments
        std::vector<Variant> params;
        buildParams(params, arguments...);

        // Call function
        const_cast<Function &>(function).call(params);
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

template <typename... Arguments>
template <typename Type, typename... Args>
void Signal<Arguments...>::buildParams(std::vector<Variant> & params, Type param, Args... args)
{
    params.push_back(Variant::fromValue<Type>(param));
    buildParams(params, args...);
}

template <typename... Arguments>
template <typename Type>
void Signal<Arguments...>::buildParams(std::vector<Variant> & params, Type param)
{
    params.push_back(Variant::fromValue<Type>(param));
}

template <typename... Arguments>
void Signal<Arguments...>::buildParams(std::vector<Variant> &)
{
}


} // namespace cppexpose
