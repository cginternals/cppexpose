
#pragma once


#include <cppexpose/base/template_helpers.h>

#include <cppexpose/typed/TypedInt.h>
#include <cppexpose/typed/TypedArray.h>


namespace cppexpose
{


/**
*  @brief
*    Class to throw compiler errors
*/
template <typename T>
class TypeError;


/**
*  @brief
*    Class to recognize unsupported types
*/
template <typename T>
class UnsupportedType : public Typed<T>
{
public:
    /*
      If you got here from a compiler error, you have tried to instanciate
      a typed value (e.g., property) for an unsupported type.

      Please create your own typed extension class for the unsupported type
      by inheriting from Typed<DataType> (and any matching abstract interfaces),
      and provide a specialization of TypeSelector<DataType> with
          using Type = DataType;
    */
    TypeError<T> error;


public:
    template <typename... Args>
    UnsupportedType(Args&&... /*args*/)
    {
    }

    virtual ~UnsupportedType()
    {
    }

    virtual std::string toString() const
    {
        return "";
    }

    virtual bool fromString(const std::string & /*string*/)
    {
        return false;
    }
};


/**
*  @brief
*    Helper class for selecting types
*
*    Specialize this class template to register a new type.
*    Define the typed class that you want to use as typedef Type.
*/
template <typename T, typename = void>
struct TypeSelector
{
    using Type = UnsupportedType<T>;
};

/**
*  @brief
*    Type selector for type int
*/
template <>
struct TypeSelector<int>
{
    using Type = TypedInt<int>;
};

/**
*  @brief
*    Property selector for properties of array types
*/
template <typename T>
struct TypeSelector<T, helper::EnableIf<helper::isArray<T>>>
{
    using Type = TypedArray<typename T::value_type, std::tuple_size<T>::value, T>;
};


} // namespace cppexpose
