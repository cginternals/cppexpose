
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/plugin/AbstractGenericComponent.h>


namespace cppexpose
{


/**
*  @brief
*    Represents a generic component of a specific type
*
*  @see
*    AbstractGenericComponent
*/
template <typename Type, typename BaseType>
class CPPEXPOSE_TEMPLATE_API GenericComponent : public AbstractGenericComponent<BaseType>
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


} // namespace cppexpose


#include <cppexpose/plugin/GenericComponent.inl>
