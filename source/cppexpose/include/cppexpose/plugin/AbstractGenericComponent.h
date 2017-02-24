
#pragma once


#include <memory>

#include <cppexpose/plugin/AbstractComponent.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class for generic components
*
*  @remarks
*    A generic component is used for classes which have not
*    defined their own component specialization via a type
*    definition (AbstractComponentType and ComponentType<Type>).
*    A generic component assumes that the class can be
*    instanciated using a default constructor.
*/
template <typename BaseType>
class AbstractGenericComponent : public AbstractComponent
{
public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractGenericComponent();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractGenericComponent();

    /**
    *  @brief
    *    Create new instance of the component
    *
    *  @return
    *    New instance
    */
    virtual std::unique_ptr<BaseType> createInstance() const = 0;
};


} // namespace cppexpose


#include <cppexpose/plugin/AbstractGenericComponent.inl>
