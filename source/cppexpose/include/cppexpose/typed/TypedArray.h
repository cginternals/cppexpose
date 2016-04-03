
#pragma once


#include <vector>
#include <array>

#include <cppexpose/typed/Typed.h>


namespace cppexpose
{


/**
*  @brief
*    Representation of a typed array
*/
template <typename T, size_t Size, typename BaseType>
class TypedArray : public Typed<BaseType>
{
public:
    typedef T ElementType;  ///< Type of an element in the array


public:
    /**
    *  @brief
    *    Constructor
    */
    TypedArray();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TypedArray();

    /**
    *  @brief
    *    Get number of element
    *
    *  @return
    *    Number of elements
    */
    size_t numElements() const;

    /**
    *  @brief
    *    Get array element
    *
    *  @param[in] i
    *    Index into array
    *
    *  @return
    *    Value
    */
    virtual T getElement(size_t i) const = 0;

    /**
    *  @brief
    *    Set array element
    *
    *  @param[in] i
    *    Index into array
    *  @param[in] value
    *    Value
    */
    virtual void setElement(size_t i, const T & value) = 0;

    // Virtual AbstractTyped interface
    virtual std::string typeName() const override;
    virtual bool isComposite() const override;
    virtual size_t numSubValues() const override;
    virtual AbstractTyped * subValue(size_t i) override;
    virtual bool isArray() const override;


protected:
    std::vector<AbstractTyped *> m_subValues; ///< Typed accessors for sub-values (lazy initialized)
};


} // namespace cppexpose


#include <cppexpose/typed/TypedArray.hpp>
