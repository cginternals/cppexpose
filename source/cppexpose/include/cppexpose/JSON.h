
#pragma once


#include <string>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractVar;
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
    *    Parse JSON from string
    *
    *  @param[in] root
    *    Typed value
    *  @param[in] outputMode
    *    JSON output mode
    *
    *  @return
    *    JSON string
    */
    static std::string stringify(const AbstractVar & root, OutputMode outputMode = Compact);

    /**
    *  @brief
    *    Load JSON from file
    *
    *  @param[in] filename
    *    Filename of JSON file
    *
    *  @return
    *    Read value, empty on error
    */
    static Variant load(const std::string & filename);

    /**
    *  @brief
    *    Parse JSON from string
    *
    *  @param[in] document
    *    JSON string
    *
    *  @return
    *    Read value, empty on error
    */
    static Variant parse(const std::string & document);
};


} // namespace cppexpose
