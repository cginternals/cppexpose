
#pragma once


#include <map>

#include <cppexpose/type/AbstractBaseType.h>


namespace cppexpose
{


/**
*  @brief
*    Abstract base class template for types.
*
*    If you want to provide your own type, it should inherit
*    from BaseTypeImpl. Then, create a specialization of
*    GetType<> to make the new type known in the type system.
*/
template <typename T, typename ET>
class CPPEXPOSE_TEMPLATE_API BaseTypeImpl : public AbstractBaseType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    BaseTypeImpl();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~BaseTypeImpl();

    // Virtual AbstractBaseType interface
    virtual bool hasElementType() const override;
    virtual std::shared_ptr<AbstractBaseType> elementType() override;
    virtual bool hasSymbolicNames() const override;
    virtual std::vector<std::string> symbolicNames() const override;

    /**
    *  @brief
    *    Get symbolic names and values
    *
    *  @return
    *    Map of symbolic names and values
    */
    const std::map<std::string, T> & namedValues() const;

    /**
    *  @brief
    *    Set symbolic names and values
    *
    *  @param[in] namedValues
    *    Map of symbolic names and values
    */
    void setNamedValues(const std::map<std::string, T> & namedValues);

    /**
    *  @brief
    *    Get default value
    *
    *  @return
    *    Default value
    */
    virtual const T & defaultValue() const = 0;

    /**
    *  @brief
    *    Convert value into string
    *
    *  @param[in] var
    *    Typed value
    *
    *  @return
    *    Converted value
    */
    virtual std::string toString(const T & var) const = 0;

    /**
    *  @brief
    *    Set value from string
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromString(T & var, const std::string & value) const = 0;

    /**
    *  @brief
    *    Convert value into boolean
    *
    *  @param[in] var
    *    Typed value
    *
    *  @return
    *    Converted value
    */
    virtual bool toBool(const T & var) const = 0;

    /**
    *  @brief
    *    Set value from boolean
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromBool(T & var, bool value) const = 0;

    /**
    *  @brief
    *    Convert value into long long
    *
    *  @param[in] var
    *    Typed value
    *
    *  @return
    *    Converted value
    */
    virtual long long toLongLong(const T & var) const = 0;

    /**
    *  @brief
    *    Set value from long long
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromLongLong(T & var, long long value) const = 0;

    /**
    *  @brief
    *    Convert value into unsigned long long
    *
    *  @param[in] var
    *    Typed value
    *
    *  @return
    *    Converted value
    */
    virtual unsigned long long toULongLong(const T & var) const = 0;

    /**
    *  @brief
    *    Set value from unsigned long long
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromULongLong(T & var, unsigned long long value) const = 0;

    /**
    *  @brief
    *    Convert value into double
    *
    *  @param[in] var
    *    Typed value
    *
    *  @return
    *    Converted value
    */
    virtual double toDouble(const T & var) const = 0;

    /**
    *  @brief
    *    Set value from double
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] value
    *    Input value
    *
    *  @return
    *    'true' if value could be set, else 'false'
    */
    virtual bool fromDouble(T & var, double value) const = 0;

    /**
    *  @brief
    *    Get number of elements of an array
    *
    *  @param[in] var
    *    Typed value
    *
    *  @return
    *    Number of elements, 1 if not an array
    *
    *  @remarks
    *    Only works if the type is an array (see isArray()).
    */
    virtual size_t numElements(const T & var) const = 0;

    /**
    *  @brief
    *    Get element of an array
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] i
    *    Index of element
    *
    *  @return
    *    Value of element, default value if index is invalid
    *
    *  @remarks
    *    Only works if the type is an array (see isArray()).
    */
    virtual ET getElement(const T & var, size_t i) const = 0;

    /**
    *  @brief
    *    Set element of an array
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] i
    *    Index of element
    *  @param[in] value
    *    Value of element
    *
    *  @remarks
    *    Only works if the type is an array (see isArray()).
    */
    virtual void setElement(T & var, size_t i, ET value) const = 0;

    /**
    *  @brief
    *    Add element to an array
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] value
    *    Value of element
    *
    *  @remarks
    *    Only works if the type is a dynamic array (see isDynamicArray()).
    *    The default implementation of this function does nothing (NOP).
    */
    virtual void push(T & var, ET value) const = 0;

    /**
    *  @brief
    *    Get list of keys of a map
    *
    *  @param[in] var
    *    Typed value
    *
    *  @return
    *    List of keys, empty list if not a map
    *
    *  @remarks
    *    Only works if the type is a map (see isMap()).
    */
    virtual std::vector<std::string> keys(const T & var) const = 0;

    /**
    *  @brief
    *    Get element of a map
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] key
    *    Key
    *
    *  @return
    *    Value of element, default value if key is invalid
    *
    *  @remarks
    *    Only works if the type is a map (see isMap()).
    */
    virtual ET getElement(const T & var, const std::string & key) const = 0;

    /**
    *  @brief
    *    Set element of a map
    *
    *  @param[in] var
    *    Typed value
    *  @param[in] key
    *    Key
    *  @param[in] value
    *    Value of element
    *
    *  @remarks
    *    Only works if the type is a map (see isMap()).
    */
    virtual void setElement(T & var, const std::string & key, ET value) const = 0;


protected:
    std::map<std::string, T> m_namedValues; ///< Map of symbolic names and values
};


} // namespace cppexpose


#include <cppexpose/type/BaseTypeImpl.inl>
