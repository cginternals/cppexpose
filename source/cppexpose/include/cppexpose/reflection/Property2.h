
#pragma once


#include <cppexpose/type/AbstractProperty.h>


namespace cppexpose
{


/**
*  @brief
*    Typed property that holds a value
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API Property : public AbstractProperty
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Property();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] value
    *    Initial value
    */
    Property(const T & value);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Property();

    // Virtual AbstractValueContainer interface
    virtual std::unique_ptr<AbstractValueContainer> createCopy() const override;

    /**
    *  @brief
    *    Get value
    *
    *  @return
    *    Value
    */
    T value() const;

    /**
    *  @brief
    *    Set value
    *
    *  @param[in] value
    *    Value
    */
    void setValue(const T & value);

    /**
    *  @brief
    *    Get pointer to value
    *
    *  @return
    *    Pointer to value (can be null)
    *
    *  @remarks
    *    Whether or not a pointer to the value can be returned
    *    depends on the actual storage type. So be aware that
    *    this function can return nullptr, if it is called
    *    for example on a ManagedValue.
    */
    const T * ptr() const;

    /**
    *  @brief
    *    Get pointer to value
    *
    *  @return
    *    Pointer to value (can be null)
    *
    *  @remarks
    *    Whether or not a pointer to the value can be returned
    *    depends on the actual storage type. So be aware that
    *    this function can return nullptr, if it is called
    *    for example on a ManagedValue.
    */
    T * ptr();

    /**
    *  @brief
    *    Get number of elements of an array
    *
    *  @return
    *    Number of elements, 1 if not an array
    *
    *  @remarks
    *    Only works if the type is an array (see isArray()).
    */
    size_t numElements() const;

    /**
    *  @brief
    *    Get element of an array
    *
    *  @param[in] i
    *    Index of element
    *
    *  @return
    *    Value of element, default value if index is invalid
    *
    *  @remarks
    *    Only works if the type is an array (see isArray()).
    */
    ElementType getElement(size_t i) const;

    /**
    *  @brief
    *    Set element of an array
    *
    *  @param[in] i
    *    Index of element
    *  @param[in] value
    *    Value of element
    *
    *  @remarks
    *    Only works if the type is an array (see isArray()).
    */
    void setElement(size_t i, ElementType value);

    /**
    *  @brief
    *    Add element to an array
    *
    *  @param[in] value
    *    Value of element
    *
    *  @remarks
    *    Only works if the type is a dynamic array (see isDynamicArray()).
    *    The default implementation of this function does nothing (NOP).
    */
    void push(ElementType value);

    /**
    *  @brief
    *    Get list of keys of a map
    *
    *  @return
    *    List of keys, empty list if not a map
    *
    *  @remarks
    *    Only works if the type is a map (see isMap()).
    */
    std::vector<std::string> keys() const;

    /**
    *  @brief
    *    Get element of a map
    *
    *  @param[in] key
    *    Key
    *
    *  @return
    *    Value of element, default value if key is invalid
    *
    *  @remarks
    *    Only works if the type is a map (see isMap()).
    */
    ElementType getElement(const std::string & key) const;

    /**
    *  @brief
    *    Set element of a map
    *
    *  @param[in] key
    *    Key
    *  @param[in] value
    *    Value of element
    *
    *  @remarks
    *    Only works if the type is a map (see isMap()).
    */
    void setElement(const std::string & key, ElementType value);
};


} // namespace cppexpose


#include <cppexpose/type/Value.inl>
