
#pragma once


#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


/**
*  @brief
*    Variant typed value
*
*    A Variant can be used to store and pass arbitrary typed values in a uniform manner.
*
*    To create a Variant from the list of supported primitive data types, use one of the
*    available constructors. To create a Variant from another data type, use the static
*    function fromValue().
*
*    The type of the stored value can be determined by type() or hasType<Type>().
*    To access the value of a variant, call value<Type>(). If the given data type does not
*    match the stored type, the value may be converted. Note that this only works for the
*    supported primitive data types. To check if a type can be converted, use canConvert<Type>().
*
*    VariantArray and VariantMap can be used to store collections or hierarchies of variants.
*    For simplified usage, use the convenience functions array() or map() to create such variants,
*    and asArray() or asMap() to access their data. These composite variants will automatically
*    be interpreted as JSON arrays or objects within scriptzeug and can be serialized by the
*    JSON tool class.
*/
class CPPEXPOSE_API Variant
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Variant();

    /**
    *  @brief
    *    Destructor
    */
    ~Variant();

    template <typename T>
    T value() const
    {
        T v;
        return v;
    }
};


} // namespace cppexpose
