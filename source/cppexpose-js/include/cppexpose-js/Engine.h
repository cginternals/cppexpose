
#pragma once


#include <string>
#include <memory>
#include <map>

#include <cppexpose/cppexpose_features.h>
#include <cppexpose/ScopedConnection.h>

#include <cppexpose-script/ScriptEngine.h>

#include <cppexpose-js/cppexpose-js_api.h>


struct duk_hthread;
typedef struct duk_hthread duk_context;


namespace cppexpose
{
    class Object;
    class Variant;
}


namespace cppexpose_js
{


class ObjectWrapper;


/**
*  @brief
*    Duktape (javascript) scripting engine
*/
class CPPEXPOSE_JS_API Engine : public cppexpose_script::ScriptEngine
{
    friend class FunctionWrapper;
    friend class ObjectWrapper;


public:
    /**
    *  @brief
    *    Constructor
    */
    Engine();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Engine();

    /**
    *  @brief
    *    Copy constructor (deleted)
    */
    Engine(const Engine & other) = delete;

    /**
    *  @brief
    *    Move constructor (deleted)
    */
    Engine(Engine && other) CPPEXPOSE_NOEXCEPT = delete;

    /**
    *  @brief
    *    Copy assignment operator (deleted)
    */
    Engine & operator=(const Engine & other) = delete;

    /**
    *  @brief
    *    Move assignment operator (deleted)
    */
    Engine & operator=(Engine && other) CPPEXPOSE_NOEXCEPT = delete;

    // Virtual ScriptEngine interface
    virtual void onAddGlobalObject(const std::string & name, cppexpose::Object * obj) override;
    virtual void onRemoveGlobalObject(const std::string & name) override;
    virtual cppexpose::Variant onEvaluate(const std::string & code) override;


protected:
    /**
    *  @brief
    *    Get duktape scripting engine from duktape context
    *
    *  @param[in] context
    *    Duktape context
    *
    *  @return
    *    Duktape scripting engine (can be null)
    */
    static Engine * getScriptEngine(duk_context * context);

    /**
    *  @brief
    *    Get value from the duktape stack and convert it into a variant
    *
    *  @param[in] context
    *    Duktape context
    *  @param[in] index
    *    Stack index
    *
    *  @return
    *    Variant value
    */
    cppexpose::Variant fromDukStack(int index = -1);

    /**
    *  @brief
    *    Push value to the duktape stack
    *
    *  @param[in] context
    *    Duktape context
    *  @param[in] value
    *    Variant value
    */
    void pushToDukStack(const cppexpose::Variant & value);

    /**
    *  @brief
    *    Get existing wrapper for object or create a new one
    *
    *  @param[in] object
    *    Object to be wrapped
    *
    *  @remarks
    *    The returned object wrapper is owned by the engine
    *    and will be deleted if either the engine or the
    *    wrapped object is destroyed
    */
    ObjectWrapper * getOrCreateObjectWrapper(cppexpose::Object * object);

    /**
    *  @brief
    *    Get index of the next free element in the stash
    *
    *  @return
    *    Index of next stash element
    */
    int getNextStashIndex();


protected:
    duk_context * m_context; ///< Duktape context (never null)

    /// Object wrappers and beforeDestroy connections
    std::map<cppexpose::Object *, std::pair<std::unique_ptr<ObjectWrapper>, cppexpose::Connection>> m_objectWrappers;
};


} // namespace cppexpose_js
