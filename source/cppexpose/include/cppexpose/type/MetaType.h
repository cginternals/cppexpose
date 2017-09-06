
#pragma once


#include <cppexpose/type/AbstractType.h>


namespace cppexpose
{


/**
*  @brief
*    The type of all abstract types.
*    The type of the MetaType is a MetaType.
*/
class CPPEXPOSE_API MetaType : public AbstractType
{
public:
    /**
    *  @brief
    *    Constructor
    */
    MetaType();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~MetaType();


    /**
    *  @brief
    *    Get type instance
    *
    *  @return
    *    Type object
    */
    virtual const AbstractType & type() const override;

    /**
    *  @brief
    *    Get type name
    *
    *  @return
    *    Type name
    */
    virtual std::string typeName() const override;

    /**
    *  @brief
    *    Check if type is an array-type
    *
    *  @return
    *    'true' if type is an array, else 'false'
    */
    virtual bool isArray() const override;

    /**
    *  @brief
    *    Check if type is an array of dynamic size
    *
    *  @return
    *    'true' if type is an array of dynamic size, else 'false'
    */
    virtual bool isDynamicArray() const override;

    /**
    *  @brief
    *    Check if type is a string-map
    *
    *  @return
    *    'true' if type is a map (e.g., std::map<std::string, T>), else 'false'
    */
    virtual bool isMap() const override;

    /**
    *  @brief
    *    Check if type is a boolean
    *
    *  @return
    *    'true' if type is a boolean, else 'false'
    */
    virtual bool isBoolean() const override;

    /**
    *  @brief
    *    Check if type is a number
    *
    *  @return
    *    'true' if type is a number, else 'false'
    */
    virtual bool isNumber() const override;

    /**
    *  @brief
    *    Check if type is an integral number
    *
    *  @return
    *    'true' if type is an integral number, else 'false'
    */
    virtual bool isIntegral() const override;

    /**
    *  @brief
    *    Check if type is an unsigned number
    *
    *  @return
    *    'true' if type is an unsigned number, else 'false'
    */
    virtual bool isUnsigned() const override;

    /**
    *  @brief
    *    Check if type is a floating point number
    *
    *  @return
    *    'true' if type is a floating point number, else 'false'
    */
    virtual bool isFloatingPoint() const override;

    /**
    *  @brief
    *    Check if type is a string
    *
    *  @return
    *    'true' if type is a string, else 'false'
    */
    virtual bool isString() const override;

    /**
    *  @brief
    *    Check if type is a type
    *
    *  @return
    *    'true' if type is a type, else 'false'
    */
    virtual bool isType() const override;
};


} // namespace cppexpose
