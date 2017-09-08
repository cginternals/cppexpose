
#pragma once


#include <memory>

#include <cppexpose/type/AbstractTyped.h>
#include <cppexpose/type/AbstractBaseType.h>


namespace cppexpose
{


/**
*  @brief
*    Type information
*/
class CPPEXPOSE_API Type : public AbstractTyped
{
public:
    //@{
    /**
    *  @brief
    *    Create type object for a basic data type
    *
    *  @tparam[in] T
    *    C++ type
    *
    *  @return
    *    Type object
    */
    template <typename T>
    static Type basicType();
    //@}


public:
    //@{
    /**
    *  @brief
    *    Constructor for an empty type
    */
    Type();

    /**
    *  @brief
    *    Constructor for a given basic type
    *
    *  @param[in] basicType
    *    Basic type
    */
    Type(const std::shared_ptr<AbstractBaseType> & basicType);

    /**
    *  @brief
    *    Copy constructor
    *
    *  @param[in] type
    *    Type that will be copied
    */
    Type(const Type & type);

    /**
    *  @brief
    *    Destructor
    */
    ~Type();

    /**
    *  @brief
    *    Assignment operator
    *
    *  @param[in] type
    *    Type that will be copied
    *
    *  @return
    *    Type object
    */
    Type & operator=(const Type & type);
    //@}

    // Virtual Typed interface
    virtual const Type & type() const override;
    virtual Type & type() override;
    virtual const Type & elementType() const override;
    virtual Type & elementType() override;
    virtual std::string typeName() const override;
    virtual bool isNull() const override;
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
    virtual bool isType() const override;
    virtual bool hasSymbolicNames() const override;
    virtual std::vector<std::string> symbolicNames() const override;


protected:
    void fork();
    bool ensureElementType() const;


protected:
    std::shared_ptr<AbstractBaseType> m_type;        ///< Base type (never null)
    mutable std::unique_ptr<Type>     m_elementType; ///< Element type (can be null)
};


} // namespace cppexpose


#include <cppexpose/type/Type.inl>
