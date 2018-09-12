
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class Variant;


/**
*  @brief
*    JSON tools
*/
class CPPEXPOSE_API JSON
{
public:
    /**
    *  @brief
    *    JSON output mode
    */
    enum OutputMode
    {
        Compact = 0, ///< Create JSON without indentation and newlines
        Beautify     ///< Create better readable JSON with indentation and newlines
    };


public:
    /**
    *  @brief
    *    Linearize JSON to string
    *
    *  @param[in] root
    *    Variant value
    *  @param[in] outputMode
    *    JSON output mode
    *
    *  @return
    *    JSON string
    */
    static std::string stringify(const Variant & root, OutputMode outputMode = Compact);

    /**
    *  @brief
    *    Linearize JSON to string
    *
    *  @param[in] stream
    *    Stream to write results to
    *  @param[in] root
    *    Variant value
    *  @param[in] outputMode
    *    JSON output mode
    */
    static void stringify(std::ostream & stream, const Variant & root, OutputMode outputMode = Compact);

    /**
    *  @brief
    *    Load JSON from file
    *
    *  @param[out] root
    *    Output variant
    *  @param[in] filename
    *    Filename of JSON file
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    static bool load(Variant & root, const std::string & filename);

    /**
    *  @brief
    *    Parse JSON from string
    *
    *  @param[out] root
    *    Output variant
    *  @param[in] document
    *    JSON string
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    static bool parse(Variant & root, const std::string & document);
};


} // namespace cppexpose
