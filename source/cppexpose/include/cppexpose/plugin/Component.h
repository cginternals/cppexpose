
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/plugin/ComponentHelpers.h>


namespace cppexpose
{


/**
*  @brief
*    Represents a concrete component that can be instanciated
*/
template <typename Type, typename BaseType>
class CPPEXPOSE_TEMPLATE_API Component : public ComponentTypes<BaseType>::template ComponentType<Type>
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
    Component(
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
    virtual ~Component();
};


} // namespace cppexpose


#include <cppexpose/plugin/Component.inl>
