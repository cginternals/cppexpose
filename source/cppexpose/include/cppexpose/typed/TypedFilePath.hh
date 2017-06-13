
#pragma once


#include <cppexpose/cppexpose_api.h>
#include <cppexpose/typed/Typed.hh>


namespace cppexpose
{


/**
*  @brief
*    Representation of a filename value
*/
template <typename T, typename BASE>
class CPPEXPOSE_TEMPLATE_API TypedFilePath : public cppexpose::Typed<T, BASE>
{
public:
    /**
    *  @brief
    *    Constructor
    */
    TypedFilePath();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedFilePath();

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
    bool isString() const override;
    std::string toString() const override;
    bool fromString(const std::string & string) override;
    Variant toVariant() const override;
    bool fromVariant(const Variant & variant) override;
};


} // namespace cppexpose
