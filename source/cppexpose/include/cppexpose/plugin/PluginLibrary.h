
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractComponent;


/**
*  @brief
*    Function to initialize a plugin library
*/
using init_ptr = void (*)();

/**
*  @brief
*    Function to deinitialize a plugin library
*/
using deinit_ptr = void (*)();

/**
*  @brief
*    Function to get the number of components contained in a library
*/
using numComponents_ptr = int (*)();

/**
*  @brief
*    Function to get a specific component of a plugin library
*/
using component_ptr = cppexpose::AbstractComponent * (*)(unsigned int);


/**
*  @brief
*    Represents a dynamic plugin library
*/
class CPPEXPOSE_API PluginLibrary 
{
public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] filePath
    *    Path to the loaded library
    */
    PluginLibrary(const std::string & filePath);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PluginLibrary();

    /**
    *  @brief
    *    Get path to library file
    *
    *  @return
    *    Path to the loaded library
    */
    const std::string & filePath() const;

    /**
    *  @brief
    *    Check if plugin library is valid
    *
    *  @return
    *    'true' if the plugin has been loaded successfully, else 'false'
    */
    bool isValid() const;

    /**
    *  @brief
    *    Initialize plugin library
    */
    void initialize();

    /**
    *  @brief
    *    De-initialize plugin library
    */
    void deinitialize();

    /**
    *  @brief
    *    Get number of components contained in the library
    *
    *  @return
    *    Number of components
    */
    unsigned int numComponents() const;

    /**
    *  @brief
    *    Get component by index
    *
    *  @param[in] index
    *    Component number
    *
    *  @return
    *    Pointer to the component, nullptr on error
    */
    cppexpose::AbstractComponent * component(unsigned int index) const;                                                                                                                                        


protected:
    std::string       m_filePath; ///< Path to the loaded library
    void            * m_handle;   ///< Library handle

    init_ptr          m_initPtr;          ///< Pointer to function init()
    deinit_ptr        m_deinitPtr;        ///< Pointer to function deinit()
    numComponents_ptr m_numComponentsPtr; ///< Pointer to function numComponents()
    component_ptr     m_componentPtr;     ///< Pointer to function component()
};


} // namespace cppexpose
