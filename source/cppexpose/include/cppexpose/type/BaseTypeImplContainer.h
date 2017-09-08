
#pragma once


#include <map>

#include <cppexpose/type/AbstractBaseType.h>


namespace cppexpose
{


/**
*  @brief
*    Implementation helper for container types
*/
template <typename T, typename ET>
class CPPEXPOSE_TEMPLATE_API BaseTypeImplContainer : public BaseTypeImpl<T, ET>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    BaseTypeImplContainer();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~BaseTypeImplContainer();

    // Virtual AbstractBaseType interface
    virtual bool hasElementType() const override;
    virtual std::shared_ptr<AbstractBaseType> elementType() override;


protected:
    std::shared_ptr<AbstractBaseType> m_elementType; ///< Type of elements
};


} // namespace cppexpose


#include <cppexpose/type/BaseTypeImplContainer.inl>
