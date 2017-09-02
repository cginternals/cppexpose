
#pragma once


#include <cppexpose/signal/Signal.h>
#include <cppexpose/type/AbstractValue.h>
#include <cppexpose/type/Type.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class for typed values
*/
template <typename T>
class CPPEXPOSE_TEMPLATE_API AbstractTypedValue : public AbstractValue
{
public:
    typedef typename Type<T>::BaseType    BaseType;
    typedef typename Type<T>::ElementType ElementType;


public:
    Signal<const T &> valueChanged; ///< Called when the value has been changed


public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractTypedValue();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractTypedValue();

    // Virtual AbstractValue interface
    virtual const AbstractType & type() const override;

    // Virtual IType interface
    virtual const std::type_info & typeInfo() const override;
    virtual std::string typeName() const override;
    virtual bool isConst() const override;
    virtual bool isArray() const override;
    virtual bool isDynamicArray() const override;
    virtual bool isMap() const override;
    virtual bool isBoolean() const override;
    virtual bool isNumber() const override;
    virtual bool isIntegral() const override;
    virtual bool isUnsigned() const override;
    virtual bool isFloatingPoint() const override;
    virtual bool isString() const override;

    /**
    *  @brief
    *    Get value
    *
    *  @return
    *    Value
    */
    virtual T value() const = 0;

    /**
    *  @brief
    *    Set value
    *
    *  @param[in] value
    *    Value
    */
    virtual void setValue(const T & value) = 0;

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
    virtual const T * ptr() const = 0;

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
    virtual T * ptr() = 0;

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
    virtual size_t numElements() const = 0;

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
    virtual ElementType getElement(size_t i) const = 0;

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
    virtual void setElement(size_t i, ElementType value) = 0;

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
    virtual void push(ElementType value) = 0;

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
    virtual std::vector<std::string> keys() const = 0;

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
    virtual ElementType getElement(const std::string & key) const = 0;

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
    virtual void setElement(const std::string & key, ElementType value) = 0;


protected:
    Type<T> m_type; ///< Object that describes the type of the value
};


} // namespace cppexpose


#include <cppexpose/type/AbstractTypedValue.inl>
