
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class Variant;


/**
*  @brief
*    Variant serializer
*/
class CPPEXPOSE_API Serializer
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Serializer();

    /**
    *  @brief
    *    Constructor
    */
    virtual ~Serializer();

    /**
    *  @brief
    *    Load Variant from file
    *
    *  @param[in] obj
    *    Variant receiving the saved value
    *  @param[in] filename
    *    File name
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    bool load(Variant & obj, const std::string & filename);

    /**
    *  @brief
    *    Save Variant to file
    *
    *  @param[in] obj
    *    Variant (object or array)
    *  @param[in] filename
    *    File name
    *
    *  @return
    *    'true' if file has been saved successfully, 'false' on error
    */
    bool save(const Variant & obj, const std::string & filename);

    /**
    *  @brief
    *    Load Variant from string
    *
    *  @param[in] obj
    *    Variant receiving the saved value
    *  @param[in] string
    *    String representation
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    virtual bool fromString(Variant & obj, const std::string & string) = 0;

    /**
    *  @brief
    *    Save Variant to string
    *
    *  @param[in] obj
    *    Variant (object or array)
    *
    *  @return
    *    String representation
    */
    virtual std::string toString(const Variant & obj) = 0;
};


} // namespace cppexpose
