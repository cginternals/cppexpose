
#pragma once


#include <cppexpose/plugin/GenericComponent.h>


namespace cppexpose
{


/**
*  @brief
*    Helper struct for SFINAE
*/
template <typename Type>
struct VoidType
{
    typedef void type;
};

/**
*  @brief
*    Determine component types for a type
*/
template <typename BaseType, typename T = void>
struct ComponentTypes
{
    using AbstractComponentType = AbstractGenericComponent<BaseType>;

    template <typename Type>
    using ComponentType = GenericComponent<Type, BaseType>;
};

/**
*  @brief
*    Determine component types for a type
*/
template <typename BaseType>
struct ComponentTypes<BaseType, typename VoidType<typename BaseType::AbstractComponentType>::type>
{
    using AbstractComponentType = typename BaseType::AbstractComponentType;

    template <typename Type>
    using ComponentType = typename BaseType::template ComponentType<Type>;
};


} // namespace cppexpose
