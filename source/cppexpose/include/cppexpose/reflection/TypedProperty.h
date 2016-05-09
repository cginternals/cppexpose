
#pragma once


#include <cppexpose/signal/Signal.h>
#include <cppexpose/reflection/AbstractProperty.h>


namespace cppexpose
{


/**
*  @brief
*    Interface for property with a specific type
*/
template <typename T>
class TypedProperty : public AbstractProperty
{
public:
    Signal<const T &> valueChanged;  ///< Called when the value has been changed


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] parent
    *    Parent object
    *  @param[in] name
    *    Property name
    *
    *  @remarks
    *    The property is created and added to the given parent object.
    */
    TypedProperty(PropertyGroup * parent, const std::string & name);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedProperty();

    // Virtual AbstractProperty interface
    virtual bool isGroup() const override;
};


} // namespace cppexpose


#include <cppexpose/reflection/TypedProperty.hpp>
