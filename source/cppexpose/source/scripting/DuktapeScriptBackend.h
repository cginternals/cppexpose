
#pragma once


#include <string>
#include <memory>
#include <map>

#include <cppexpose/cppexpose_features.h>
#include <cppexpose/scripting/AbstractScriptBackend.h>
#include <cppexpose/signal/ScopedConnection.h>

#include "duktape-1.4.0/duktape.h"


namespace cppexpose
{


class Object;
class DuktapeObjectWrapper;


/**
*  @brief
*    Duktape (javascript) scripting backend
*/
class CPPEXPOSE_API DuktapeScriptBackend : public AbstractScriptBackend
{
    friend class DuktapeScriptFunction;
    friend class DuktapeObjectWrapper;


public:
    /**
    *  @brief
    *    Constructor
    */
    DuktapeScriptBackend();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DuktapeScriptBackend();

    /**
    *  @brief
    *    Copy constructor (deleted)
    */
    DuktapeScriptBackend(const DuktapeScriptBackend & other) = delete;

    /**
    *  @brief
    *    Move constructor (deleted)
    */
    DuktapeScriptBackend(DuktapeScriptBackend && other) CPPEXPOSE_NOEXCEPT = delete;

    /**
    *  @brief
    *    Copy assignment operator (deleted)
    */
    DuktapeScriptBackend & operator=(const DuktapeScriptBackend & other) = delete;

    /**
    *  @brief
    *    Move assignment operator (deleted)
    */
    DuktapeScriptBackend & operator=(DuktapeScriptBackend && other) CPPEXPOSE_NOEXCEPT = delete;

    // Virtual AbstractScriptBackend interface
    virtual void initialize(ScriptContext * scriptContext) override;
    virtual void addGlobalObject(const std::string & name, Object * obj) override;
    virtual void removeGlobalObject(const std::string & name) override;
    virtual Variant evaluate(const std::string & code) override;


protected:
    /**
    *  @brief
    *    Get duktape scripting backend from duktape context
    *
    *  @param[in] context
    *    Duktape context
    *
    *  @return
    *    Duktape scripting backend (can be null)
    */
    static DuktapeScriptBackend * getScriptBackend(duk_context * context);

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
    Variant fromDukStack(duk_idx_t index = -1);

    /**
    *  @brief
    *    Push value to the duktape stack
    *
    *  @param[in] context
    *    Duktape context
    *  @param[in] value
    *    Variant value
    */
    void pushToDukStack(const Variant & value);

    /**
    *  @brief
    *    Get existing wrapper for object or create a new one
    *
    *  @param[in] object
    *    Object to be wrapped
    *
    *  @remarks
    *    The returned object wrapper is owned by the backend
    *    and will be deleted if either the backend or the
    *    wrapped object is destroyed
    */
    DuktapeObjectWrapper * getOrCreateObjectWrapper(cppexpose::Object * object);

    /**
    *  @brief
    *    Get index of the next free element in the stash
    *
    *  @return
    *    Index of next stash element
    */
    int getNextStashIndex();


protected:
    duk_context                                                                    * m_context;        ///< Duktape context (never null)
    std::map<Object *, std::pair<std::unique_ptr<DuktapeObjectWrapper>, Connection>> m_objectWrappers; ///< Object wrappers + beforeDestroy connections
};


} // namespace cppexpose
