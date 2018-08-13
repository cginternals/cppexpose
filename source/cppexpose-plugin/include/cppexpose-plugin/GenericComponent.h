
#pragma once


#include <cppexpose-plugin/AbstractGenericComponent.h>


namespace cppexpose_plugin
{


/**
*  @brief
*    Represents a generic component of a specific type
*
*  @see
*    AbstractGenericComponent
*/
template <typename Type, typename BaseType>
class CPPEXPOSE_PLUGIN_TEMPLATE_API GenericComponent : public AbstractGenericComponent<BaseType>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    GenericComponent();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~GenericComponent();

    // Virtual AbstractGenericComponent<BaseType> interface
    virtual std::unique_ptr<BaseType> createInstance() const override;
};


} // namespace cppexpose_plugin


#include <cppexpose-plugin/GenericComponent.inl>
