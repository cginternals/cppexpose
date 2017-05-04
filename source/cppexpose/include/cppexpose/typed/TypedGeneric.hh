
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/typed/Typed.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of an arbitrary (unknown typed) value
*/
template <typename T, typename BASE>
class CPPEXPOSE_TEMPLATE_API TypedGeneric : public Typed<T, BASE>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedGeneric();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedGeneric();

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
};


} // namespace cppexpose
