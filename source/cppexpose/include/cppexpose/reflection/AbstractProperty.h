
#pragma once


#include <string>

#include <cppexpose/signal/Signal.h>
#include <cppexpose/typed/AbstractTyped.h>
#include <cppexpose/variant/Variant.h>


namespace cppexpose
{


class Object;


/**
*  @brief
*    Base class for properties
*/
class CPPEXPOSE_API AbstractProperty : public AbstractTyped
{
    friend class Object;


public:
    Signal<AbstractProperty *>  beforeDestroy; ///< Called before a property is destroyed
    Signal<const std::string &> optionChanged; ///< Called when an option of the property has been changed


public:
    /**
    *  @brief
    *    Constructor
    */
    AbstractProperty();

    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] options
    *    Options with which the property is initialized
    */
    AbstractProperty(const Variant & options);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractProperty();

    /**
    *  @brief
    *    Get name
    *
    *  @return
    *    Name
    */
    const std::string & name() const;

    /**
    *  @brief
    *    Set name
    *
    *  @param[in] name
    *    Name
    *
    *  @remarks
    *    This function should never be called after the property has been added to
    *    a parent object. The name change will not be updated in the parent container.
    */
    void setName(const std::string & name);

    /**
    *  @brief
    *    Get qualified name
    *
    *  @param[in] relativeRoot (optional)
    *    Root object for relative name resolution
    *
    *  @return
    *    Qualified name
    *
    *  @remark
    *    Returns ablosute qualified name if \a relativeRoot is not found in ancestral hierarchy
    */
    std::string qualifiedName(const Object * relativeRoot = nullptr) const;

    /**
    *  @brief
    *    Get parent object
    *
    *  @return
    *    Parent (can be null)
    */
    Object * parent() const;

    /**
    *  @brief
    *    Finds out whether the Object has a parent
    *
    *  @return
    *    false if the parent is null, otherwise true
    */
    bool hasParent() const;

    /**
    *  @brief
    *    Check if property is an object
    *
    *  @return
    *    'true' if property is an object, else 'false'
    */
    virtual bool isObject() const = 0;

    /**
    *  @brief
    *    Get options of property
    *
    *    Options provide additional meta information about a property.
    *    Use options to add, e.g., minimum and maximum values,
    *    affixes, or flags. These can be used to configure editor widgets.
    *    Look at the class documentation of the specific property type to
    *    get a list of supported options.
    *
    *  @return
    *    List of options
    */
    const VariantMap & options() const;

    /**
    *  @brief
    *    Set options of property
    *
    *  @param[in] map
    *    List of options
    */
    void setOptions(const VariantMap & map);

    /**
    *  @brief
    *    Check if option is set
    *
    *  @param[in] key
    *    Option name
    *
    *  @return
    *    'true' if the option is set, else 'false'
    */
    bool hasOption(const std::string & key) const;

    /**
    *  @brief
    *    Get option of property
    *
    *  @param[in] key
    *    Option name
    *
    *  @return
    *    Option value
    */
    const Variant & option(const std::string & key) const;

    /**
    *  @brief
    *    Get option of property convert to a specific type
    *
    *  @param[in] key
    *    Option name
    *  @param[in] defaultValue
    *    Default value
    *
    *  @return
    *    Option value converted to Type, defaultValue if the option doesn't exist or couldn't be converted
    */
    template <typename Type>
    Type option(const std::string & key, const Type & defaultValue = Type()) const;

    /**
    *  @brief
    *    Set option of property
    *
    *  @param[in] key
    *    Option name
    *  @param[in] value
    *    Option value
    */
    void setOption(const std::string & key, const Variant & value);

    /**
    *  @brief
    *    Remove option of property
    *
    *  @param[in] key
    *    Option name
    *
    *  @return
    *    'true' if the option has been removed, else 'false'
    */
    bool removeOption(const std::string & key);


protected:
    /**
    *  @brief
    *    Initialize property
    *
    *  @param[in] name
    *    Name (can be empty)
    *  @param[in] parent
    *    Parent object (can be null)
    *  @param[in] ownership
    *    Property ownership
    *
    *  @remarks
    *    The internal parent is updated to the parent parameter.
    *    Do not set m_parent before calling this function, otherwise
    *    the property might be rejected when added to the parent.
    */
    void initProperty(const std::string & name, Object * parent);

    /**
    *  @brief
    *    Set parent object
    *
    *  @param[in] parent
    *    Parent object (can be null)
    *
    *  @remarks
    *    This function should only be called by Object
    *    when adding or removing properties.
    */
    void setParent(Object * parent);

    /**
    *  @brief
    *    Called when an option of the property has changed
    *
    *  @param[in] option
    *    Name of the option
    *
    *  @remarks
    *    This function is empty be default and can be implemented
    *    in derived classes.
    */
    virtual void onOptionChanged(const std::string & option);


protected:
    std::string   m_name;    ///< Name of the property
    Object      * m_parent;  ///< Parent object
    VariantMap    m_options; ///< Additional options for the property (e.g., minimum or maximum values)
};


} // namespace cppexpose


#include <cppexpose/reflection/AbstractProperty.inl>
