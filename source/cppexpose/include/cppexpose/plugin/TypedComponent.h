
#pragma once


#include <cppexpose/plugin/AbstractComponent.h>


namespace cppexpose
{


/**
*  @brief
*    Represents a component of a specific type
*/
template <typename Type, typename Enable = void>
class TypedComponent : public AbstractComponent
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] name
    *    Component name
    *  @param[in] description
    *    Component description
    *  @param[in] type
    *    Component type
    *  @param[in] tags
    *    Component tags (user-defined, space-separated)
    *  @param[in] icon
    *    Icon name or ID (user-defined)
    *  @param[in] annotations
    *    Component annotations (user-defined)
    *  @param[in] vendor
    *    Vendor name
    *  @param[in] version
    *    Component version
    */
    TypedComponent(
      const std::string & name
    , const std::string & description
    , const std::string & type
    , const std::string & tags
    , const std::string & icon
    , const std::string & annotations
    , const std::string & vendor
    , const std::string & version);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedComponent();

    /**
    *  @brief
    *    Create new instance of the component
    *
    *  @return
    *    New instance
    */
    virtual Type * createInstance() const = 0;
};


} // namespace cppexpose


#include <cppexpose/plugin/TypedComponent.inl>
